const PSMoveClickerAPI = require("./build/Release/PSMoveClickerAPI");

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
 * Gets color of controller with index
 *
 * @param {Number} controllerIndex Index of the controller
 * @returns {RGB} color
 */
const GetControllerColor = (controllerIndex) => {
    if (typeof controllerIndex !== "number")
        throw "Invalid arguments, expected: GetControllerColor(number)";
    return PSMoveClickerAPI.GetControllerColor(controllerIndex);
};

/**
 * Sets color of controller with index
 *
 * @param {Number} controllerIndex Index of the controller
 * @param {Number} r red color (0-255)
 * @param {Number} g green color (0-255)
 * @param {Number} b blue color (0-255)
 */
const SetControllerColor = (controllerIndex, r, g, b) => {
    if (
        typeof controllerIndex !== "number" ||
        typeof r !== "number" ||
        typeof g !== "number" ||
        typeof b !== "number"
    )
        throw "Invalid arguments, expected: SetControllerColor(number, number, number, number)";
    PSMoveClickerAPI.SetControllerColor(controllerIndex, r, g, b);
};

module.exports = {
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
