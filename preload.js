const { contextBridge } = require("electron");
const PSMoveClickerAPI = require("./PSMoveClickerAPI/PSMoveClickerAPI");

contextBridge.exposeInMainWorld("PSMoveClickerAPI", PSMoveClickerAPI);