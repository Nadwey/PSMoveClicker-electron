import "./App.css";
import "mdb-react-ui-kit/dist/css/mdb.min.css";
import {
    MDBNavbar,
    MDBContainer,
    MDBBtn,
    MDBNavbarBrand,
    MDBTabs,
    MDBTabsItem,
    MDBTabsLink,
    MDBTabsContent,
    MDBTabsPane,
    MDBTable,
    MDBTableHead,
    MDBTableBody,
    MDBInput,
    MDBCheckbox,
} from "mdb-react-ui-kit";
import { useEffect, useState, createRef } from "react";
import Notiflix from "notiflix";

export default function App() {
    /**
     * @type {[import("../PSMoveClickerAPI/PSMoveClickerAPI").ControllerInfo[]]
     */
    const [controllerInfoList, setControllerInfoList] = useState([]);
    const [basicActive, setBasicActive] = useState("controlTab");

    const handleBasicClick = (value) => {
        if (value === basicActive) return;
        setBasicActive(value);
    };

    // Intervals
    useEffect(() => {
        const interval = setInterval(() => {
            if (PSMoveClickerAPI.IsConnected()) Notiflix.Loading.remove();
            else {
                Notiflix.Loading.dots("Connecting to PSMoveService");
            }
        }, 1000 * 2);
        return () => clearInterval(interval);
    }, []);

    useEffect(() => {
        const interval = setInterval(() => {
            if (!PSMoveClickerAPI.IsConnected()) return;
            Notiflix.Loading.remove();
            setControllerInfoList(PSMoveClickerAPI.GetInfo());
        }, 1000 / 6);
        return () => clearInterval(interval);
    }, []);

    useEffect(() => {
        const interval = setInterval(() => {
            PSMoveClickerAPI.Update();
        }, 1000 / 100);
        return () => clearInterval(interval);
    }, []);

    /**
     * @param {import("../PSMoveClickerAPI/PSMoveClickerAPI").ControllerInfo} controllerInfo
     */
    const ControllerElement = (controllerInfo) => {
        return (
            <tr
                style={{ cursor: "pointer", userSelect: "none" }}
                onClick={() => {
                    PSMoveClickerAPI.SetControllerColor(
                        controllerInfo.ID,
                        255,
                        255,
                        255
                    );
                }}
                key={`pad-${controllerInfo.ID}`}
                className={
                    controllerInfo.IsMainPad &&
                    PSMoveClickerAPI.GetIsADOFAIMode()
                        ? "table-primary"
                        : ""
                }
            >
                <th scope="row">{controllerInfo.ID}</th>
                <td>{controllerInfo.Battery}</td>
                <td>{controllerInfo.RefreshRate.toFixed(2)}</td>
            </tr>
        );
    };

    return (
        <div>
            <MDBTabs className="mb-3">
                <MDBTabsItem>
                    <MDBTabsLink
                        onClick={() => handleBasicClick("controlTab")}
                        active={basicActive === "controlTab"}
                    >
                        Control
                    </MDBTabsLink>
                </MDBTabsItem>
                <MDBTabsItem>
                    <MDBTabsLink
                        onClick={() => handleBasicClick("aboutTab")}
                        active={basicActive === "aboutTab"}
                    >
                        About
                    </MDBTabsLink>
                </MDBTabsItem>
            </MDBTabs>

            <MDBTabsContent>
                <MDBTabsPane show={basicActive === "controlTab"}>
                    <h2>Settings</h2>
                    <MDBInput
                        onChange={(e) => {
                            PSMoveClickerAPI.SetForce(
                                parseFloat(e.target.value)
                            );
                        }}
                        defaultValue="-4"
                        wrapperStyle={{ maxWidth: "200px", margin: "10px 0" }}
                        label="Swing force"
                        type="number"
                    />
                    <MDBCheckbox
                        onChange={(e) => {
                            PSMoveClickerAPI.SetIsADOFAIMode(e.target.checked);
                            console.log(e.target.checked);
                        }}
                        label="ADOFAI mode"
                    ></MDBCheckbox>

                    <br />
                    <br />
                    <h2>Controllers</h2>

                    <MDBTable>
                        <MDBTableHead>
                            <tr>
                                <th scope="col">ID</th>
                                <th scope="col">Battery</th>
                                <th scope="col">Refresh Rate</th>
                            </tr>
                        </MDBTableHead>
                        <MDBTableBody>
                            {controllerInfoList.map((val) =>
                                ControllerElement(val)
                            )}
                        </MDBTableBody>
                    </MDBTable>
                </MDBTabsPane>
                <MDBTabsPane show={basicActive === "aboutTab"}>
                    TODO
                </MDBTabsPane>
            </MDBTabsContent>
        </div>
    );
}
