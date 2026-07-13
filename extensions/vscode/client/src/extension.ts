import * as path from "path";
import { ExtensionContext, window } from "vscode";
import {
  LanguageClient,
  LanguageClientOptions,
  ServerOptions,
  TransportKind,
} from "vscode-languageclient/node";

let client: LanguageClient | null = null;

export function activate(context: ExtensionContext) {
  const serverModule = context.asAbsolutePath(
    path.join("out", "server", "server.js"),
  );

  const serverOptions: ServerOptions = {
    run: {
      module: serverModule,
      transport: TransportKind.ipc,
    },
    debug: {
      module: serverModule,
      transport: TransportKind.ipc,
      options: {
        execArgv: ["--inspect=6009"],
      },
    },
  };

  const clientOptions: LanguageClientOptions = {
    documentSelector: [{ scheme: "file", language: "kai" }],
  };

  client = new LanguageClient(
    "kai-language-server",
    "Kai Language Server",
    serverOptions,
    clientOptions,
  );

  client.registerProposedFeatures();

  client.start();

  window.showInformationMessage("Kai Language Server started");
}

export function deactivate(): Thenable<void> | undefined {
  if (!client) return undefined;
  return client.stop();
}
