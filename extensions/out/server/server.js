"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || (function () {
    var ownKeys = function(o) {
        ownKeys = Object.getOwnPropertyNames || function (o) {
            var ar = [];
            for (var k in o) if (Object.prototype.hasOwnProperty.call(o, k)) ar[ar.length] = k;
            return ar;
        };
        return ownKeys(o);
    };
    return function (mod) {
        if (mod && mod.__esModule) return mod;
        var result = {};
        if (mod != null) for (var k = ownKeys(mod), i = 0; i < k.length; i++) if (k[i] !== "default") __createBinding(result, mod, k[i]);
        __setModuleDefault(result, mod);
        return result;
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
const node_1 = require("vscode-languageserver/node");
const vscode_languageserver_textdocument_1 = require("vscode-languageserver-textdocument");
const child_process_1 = require("child_process");
const path = __importStar(require("path"));
const fs = __importStar(require("fs"));
const os = __importStar(require("os"));
const connection = (0, node_1.createConnection)(node_1.ProposedFeatures.all);
const documents = new node_1.TextDocuments(vscode_languageserver_textdocument_1.TextDocument);
let kaiBinaryPath = null;
let workspaceRoot = null;
function findKaiBinary() {
    const searchPaths = [];
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
        }
        catch {
            continue;
        }
    }
    return null;
}
function uriToFilePath(uri) {
    if (!uri.startsWith("file://"))
        return null;
    const p = uri.slice(7);
    return os.platform() === "win32" ? p.replace(/\//g, "\\") : p;
}
connection.onInitialize((params) => {
    workspaceRoot = params.rootUri ? uriToFilePath(params.rootUri) : null;
    kaiBinaryPath = findKaiBinary();
    if (kaiBinaryPath) {
        connection.console.info(`Kai compiler found at: ${kaiBinaryPath}`);
    }
    else {
        connection.console.warn("Kai compiler binary not found. Diagnostics will not be available.");
    }
    return {
        capabilities: {
            textDocumentSync: node_1.TextDocumentSyncKind.Incremental,
        },
    };
});
function parseDiagnosticLine(line) {
    const match = line.match(/^(.+?):(\d+):(\d+):\s*(error|warning)\[([^\]]+)\]:\s*(.+)$/);
    if (!match)
        return null;
    const [, , lineStr, colStr, severity, code, message] = match;
    const lineNum = Math.max(0, parseInt(lineStr, 10) - 1);
    const colNum = Math.max(0, parseInt(colStr, 10) - 1);
    return {
        range: node_1.Range.create(node_1.Position.create(lineNum, colNum), node_1.Position.create(lineNum, colNum + 1)),
        severity: severity === "error"
            ? node_1.DiagnosticSeverity.Error
            : node_1.DiagnosticSeverity.Warning,
        code,
        source: "kai",
        message: `[${code}] ${message}`,
    };
}
async function validateDocument(document) {
    if (!kaiBinaryPath)
        return;
    const filePath = uriToFilePath(document.uri);
    if (!filePath)
        return;
    const diagnostics = [];
    try {
        const combined = await new Promise((resolve, reject) => {
            (0, child_process_1.execFile)(kaiBinaryPath, ["check", filePath], {
                cwd: workspaceRoot ?? path.dirname(filePath),
                timeout: 10000,
                maxBuffer: 1024 * 1024,
            }, (err, stdout, stderr) => {
                resolve((stdout || "") + "\n" + (stderr || ""));
            });
        });
        for (const line of combined.split("\n")) {
            const diagnostic = parseDiagnosticLine(line);
            if (diagnostic)
                diagnostics.push(diagnostic);
        }
    }
    catch (e) {
        if (e && e.stderr) {
            for (const line of e.stderr.split("\n")) {
                const diagnostic = parseDiagnosticLine(line);
                if (diagnostic)
                    diagnostics.push(diagnostic);
            }
        }
        if (e && e.stdout) {
            for (const line of e.stdout.split("\n")) {
                const diagnostic = parseDiagnosticLine(line);
                if (diagnostic)
                    diagnostics.push(diagnostic);
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
//# sourceMappingURL=server.js.map