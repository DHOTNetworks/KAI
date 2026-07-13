import {
  createConnection,
  TextDocuments,
  ProposedFeatures,
  InitializeParams,
  InitializeResult,
  Diagnostic,
  DiagnosticSeverity,
  Position,
  Range,
  TextDocumentSyncKind,
} from "vscode-languageserver/node";
import { TextDocument } from "vscode-languageserver-textdocument";
import { execFile } from "child_process";
import * as path from "path";
import * as fs from "fs";
import * as os from "os";

const connection = createConnection(ProposedFeatures.all);
const documents = new TextDocuments(TextDocument);

let kaiBinaryPath: string | null = null;
let workspaceRoot: string | null = null;

function findKaiBinary(): string | null {
  const searchPaths: string[] = [];

  const serverDir = __dirname;
  const extRoot = path.resolve(serverDir, "..", "..");

  searchPaths.push(path.join(extRoot, "..", "..", "kai-linux"));
  searchPaths.push(path.join(extRoot, "..", "..", "kai-macos"));
  searchPaths.push(path.join(extRoot, "..", "..", "dist", `kai-${os.platform()}-${os.arch()}`, "kai"));

  if (process.env.PATH) {
    for (const dir of process.env.PATH.split(path.delimiter)) {
      for (const name of ["kai", "kai-linux", "kai-macos"]) {
        searchPaths.push(path.join(dir, name));
      }
    }
  }

  for (const p of searchPaths) {
    try {
      if (fs.existsSync(p)) {
        fs.accessSync(p, fs.constants.X_OK);
        return path.resolve(p);
      }
    } catch {
      continue;
    }
  }

  return null;
}

function uriToFilePath(uri: string): string | null {
  if (!uri.startsWith("file://")) return null;
  const p = uri.slice(7);
  return os.platform() === "win32" ? p.replace(/\//g, "\\") : p;
}

connection.onInitialize((params: InitializeParams): InitializeResult => {
  workspaceRoot = params.rootUri ? uriToFilePath(params.rootUri) : null;
  kaiBinaryPath = findKaiBinary();

  if (kaiBinaryPath) {
    connection.console.info(`Kai compiler found at: ${kaiBinaryPath}`);
  } else {
    connection.console.warn("Kai compiler binary not found. Diagnostics will not be available.");
  }

  return {
    capabilities: {
      textDocumentSync: TextDocumentSyncKind.Incremental,
    },
  };
});

function parseDiagnosticLine(line: string): Diagnostic | null {
  const match = line.match(
    /^(.+?):(\d+):(\d+):\s*(error|warning)\[([^\]]+)\]:\s*(.+)$/,
  );
  if (!match) return null;

  const [, , lineStr, colStr, severity, code, message] = match;
  const lineNum = Math.max(0, parseInt(lineStr, 10) - 1);
  const colNum = Math.max(0, parseInt(colStr, 10) - 1);

  return {
    range: Range.create(
      Position.create(lineNum, colNum),
      Position.create(lineNum, colNum + 1),
    ),
    severity:
      severity === "error"
        ? DiagnosticSeverity.Error
        : DiagnosticSeverity.Warning,
    code,
    source: "kai",
    message: `[${code}] ${message}`,
  };
}

async function validateDocument(document: TextDocument): Promise<void> {
  if (!kaiBinaryPath) return;

  const filePath = uriToFilePath(document.uri);
  if (!filePath) return;

  const diagnostics: Diagnostic[] = [];

  try {
    const combined = await new Promise<string>((resolve, reject) => {
      execFile(
        kaiBinaryPath!,
        ["check", filePath],
        {
          cwd: workspaceRoot ?? path.dirname(filePath),
          timeout: 10000,
          maxBuffer: 1024 * 1024,
        },
        (err, stdout, stderr) => {
          resolve((stdout || "") + "\n" + (stderr || ""));
        },
      );
    });

    for (const line of combined.split("\n")) {
      const diagnostic = parseDiagnosticLine(line);
      if (diagnostic) diagnostics.push(diagnostic);
    }
  } catch (e: any) {
    if (e && e.stderr) {
      for (const line of e.stderr.split("\n")) {
        const diagnostic = parseDiagnosticLine(line);
        if (diagnostic) diagnostics.push(diagnostic);
      }
    }
    if (e && e.stdout) {
      for (const line of e.stdout.split("\n")) {
        const diagnostic = parseDiagnosticLine(line);
        if (diagnostic) diagnostics.push(diagnostic);
      }
    }
  }

  connection.sendDiagnostics({ uri: document.uri, diagnostics });
}

documents.onDidChangeContent((change) => { validateDocument(change.document); });
documents.onDidOpen((event) => { validateDocument(event.document); });
documents.onDidSave((event) => { validateDocument(event.document); });

documents.listen(connection);
connection.listen();
