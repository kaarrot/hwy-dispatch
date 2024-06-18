Comparison static vs dynamic dispatch using portable vector intrinsics.

# Build Highway

## Windows - RelWithDebInfo
```
mkdir __build
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build . --target install --config RelWithDebInfo
```

## Linux
```
mkdir __build_linux
cmake ..
make -j 8 install
```


# VScode - CMake

```
{
    "window.enableMenuBarMnemonics": false,
    "workbench.colorTheme": "tangotango",
    // "cmake.configureOnOpen": false,
    "extensions.ignoreRecommendations": true,
    "cmake.buildDirectory": "${workspaceFolder}/__build_vscode_${buildType}_${buildKitVendor}",
    // In order to use /m flag on Windows, parallel job needs to = 1
    // This will remove -j flag from cmake command and wont suppress /m
    "cmake.parallelJobs": 8,
    "editor.codeLens": false,
    // This is Windows specific and will oversubscribe but run in low priority and won't slow down UI
    "cmake.buildToolArgs": [
        // "/m",
        // "/lowPriority"
    ],
    "security.workspace.trust.untrustedFiles": "open",
    "dotnet.help.firstView": "gettingStarted",
    "extensions.confirmedUriHandlerExtensionIds": [
        "ms-dotnettools.dotnet-interactive-vscode",
        "ms-dotnettools.vscode-dotnet-pack"
    ],
    "git.openRepositoryInParentFolders": "never",
    "C_Cpp.intelliSenseEngineFallback": "enabled",
    "cmake.configureOnOpen": false,
    "cmake.options.statusBarVisibility": "visible",
    "explorer.confirmDragAndDrop": false,
    "terminal.integrated.enableMultiLinePasteWarning": false,
}
```

# Windows
```
git config --global core.autocrlf true
```