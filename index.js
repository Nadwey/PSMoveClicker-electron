const { app, BrowserWindow, ipcMain } = require("electron");
const path = require("path");
const isDev = require("electron-is-dev");
require("@electron/remote/main").initialize();

async function createWindow() {
    const mainWindow = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: path.join(__dirname, "preload.js"),
            backgroundThrottling: false
        },
    });

    require("@electron/remote/main").enable(mainWindow.webContents);
    if (isDev) {
        mainWindow.setMenuBarVisibility(false);
        const waitOn = require("wait-on");
        await waitOn({ resources: ["http://localhost:3000"] });
        await mainWindow.loadURL("http://localhost:3000");
    } else {
        mainWindow.setMenu(null);
        mainWindow.loadURL(path.join(__dirname, "./build/index.html"));
    }
}

app.whenReady().then(() => {
    createWindow();

    app.on("activate", function () {
        if (BrowserWindow.getAllWindows().length === 0) createWindow();
    });
});

app.on("window-all-closed", function () {
    require("./PSMoveClickerAPI/PSMoveClickerAPI").Stop();
    if (process.platform !== "darwin") app.quit();
});
