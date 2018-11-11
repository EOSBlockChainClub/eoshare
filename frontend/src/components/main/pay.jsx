import React, { Component } from "react";
import Dialog from "rc-dialog";
import { Tag, Input, Button } from "antd";
import { navigate } from "gatsby";
import "./pay.scss";
class Pay extends Component {
  render() {
    const { visible, onClose, ...props } = this.props;
    return (
      <Dialog
        visible={visible}
        onClose={onClose}
        maskAnimation="slideDown"
        {...props}
        footer={
          <div
            style={{ display: "flex", flexDirection: "column", marginTop: 7 }}
          >
            <span className="pay-smart">smart contract : eoshare.download</span>
            <div style={{ display: "inline-flex" }}>
              <Input suffix="SHARE" style={{ marginRight: 20 }} value={3} />
              <Button
                style={{ padding: "0 24px" }}
                type="primary"
                onClick={() => {
                  navigate("/purchased");
                }}
              >
                BUY
              </Button>
            </div>
          </div>
        }
      >
        <div
          style={{
            display: "flex",
            flexDirection: "row",
            justifyContent: "space-between",
            width: "100%"
          }}
        >
          <div
            style={{
              display: "flex",
              flexDirection: "column",
              justifyContent: "space-between",
              width: "100%"
            }}
          >
            <Tag color="#1890ff" style={{ width: 52 }}>
              MUSIC
            </Tag>
            <span className="pay-filename">Yuna</span>
            <span className="pay-displayname">Ms. Shayna Connelly</span>
          </div>
          <div>
            <span className="pay-downloads">Downloads</span>
            <div className="pay-data">185</div>
            <div className="pay-seed">Seed</div>
            <div className="pay-data">53</div>
          </div>
        </div>
      </Dialog>
    );
  }
}

export default Pay;
