const PSMoveClickerAPI = require("./build/Release/PSMoveClickerAPI");

/**
 * Checks if is initialized
 *
 * @returns {Boolean} is initialized
 */
 const IsInitialized = () => {
    return PSMoveClickerAPI.IsInitialized();
};

/**
 * Checks if is connected
 *
 * @returns {Boolean} is connected
 */
 const IsConnected = () => {
    return PSMoveClickerAPI.IsConnected();
};

/**
 * Starts PSMoveClickerAPI
 * If an instance is arleady running, this will fail
 *
 * @returns {Boolean} Returns true if succeeded, false if fails
 */
const Start = () => {
    return PSMoveClickerAPI.Start();
};

/**
 * Stops PSMoveClickerAPI
 *
 * @returns {Boolean} Returns true if succeeded, false if fails
 */
const Stop = () => {
    return PSMoveClickerAPI.Stop();
};

/**
 * Updates PSMoveClient messages and processes them
 */
const Update = () => {
    PSMoveClickerAPI.Update();
};

/**
 * @typedef ControllerInfo
 * @type {object}
 * @property {string} Battery battery status
 * @property {number} ID controller id
 * @property {boolean} IsMainPad is main controller
 * @property {Number} RefreshRate
 */

/**
 * Gets info about PSMoveClickerAPI controllers
 *
 * @returns {Array.<ControllerInfo>}
 */
const GetInfo = () => {
    return PSMoveClickerAPI.GetInfo();
};

/**
 * Returns force of the swing
 *
 * @returns {Number} force of the swing
 */
const GetForce = () => {
    return PSMoveClickerAPI.GetForce();
};

/**
 * Sets force of the swing
 *
 * @param {Number} force force of the swing
 */
const SetForce = (force) => {
    if (typeof force !== "number")
        throw "Invalid arguments, expected: SetForce(number)";
    PSMoveClickerAPI.SetForce(force);
};

/**
 * Returns state of ADOFAI mode
 *
 * @returns {Boolean} is ADOFAI mode enabled
 */
const GetIsADOFAIMode = () => {
    return PSMoveClickerAPI.GetIsADOFAIMode();
};

/**
 * Sets state of ADOFAI mode
 *
 * @param {Boolean} ADOFAIMode ADOFAI mode enabled
 */
const SetIsADOFAIMode = (ADOFAIMode) => {
    if (typeof ADOFAIMode !== "boolean")
        throw "Invalid arguments, expected: SetIsADOFAIMode(boolean)";
    PSMoveClickerAPI.SetIsADOFAIMode(ADOFAIMode);
};

/**
 * @typedef RGB
 * @type {object}
 * @property {Number} r red color (0-255)
 * @property {Number} g green color (0-255)
 * @property {Number} b blue color (0-255)
 */

/**
 * Gets color of controller with ID
 * if the controller doesn't exists returns null
 *
 * @param {Number} controllerID ID of the controller
 * @returns {?RGB} color
 */
const GetControllerColor = (controllerID) => {
    if (typeof controllerID !== "number")
        throw "Invalid arguments, expected: GetControllerColor(number)";
    return PSMoveClickerAPI.GetControllerColor(controllerID);
};

/**
 * Sets color of controller with ID
 * if the controller doesn't exists throws
 *
 * @param {Number} controllerID ID of the controller
 * @param {Number} r red color (0-255)
 * @param {Number} g green color (0-255)
 * @param {Number} b blue color (0-255)
 */
const SetControllerColor = (controllerID, r, g, b) => {
    if (
        typeof controllerID !== "number" ||
        typeof r !== "number" ||
        typeof g !== "number" ||
        typeof b !== "number"
    )
        throw "Invalid arguments, expected: SetControllerColor(number, number, number, number)";
    if (!PSMoveClickerAPI.SetControllerColor(controllerID, r, g, b)) throw "Failed to set controller color, it doesn't exist";
};

module.exports = {
    IsConnected,
    IsInitialized,
    Start,
    Stop,
    Update,
    GetInfo,
    GetForce,
    SetForce,
    GetIsADOFAIMode,
    SetIsADOFAIMode,
    GetControllerColor,
    SetControllerColor
};
