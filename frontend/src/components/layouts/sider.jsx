import React, { Component } from "react";
import { Layout, Menu, Icon, Button, Badge } from "antd";
import { navigate } from "gatsby";
import styles from "./sider.module.scss";
const { Sider } = Layout;
class SideMenu extends Component {
  render() {
    const { current } = this.props;
    return (
      <Sider
        width={240}
        style={{
          background: "#fafafa",
          minHeight: 800,
          height: "100vh",
          position: "relative",
          zIndex: 1,
          boxShadow:
            "0 0 1px -1px rgba(0, 0, 0, 0.2), 0 1px 1px 0 rgba(0, 0, 0, 0.12), 0 4px 1px 0 rgba(0, 0, 0, 0.14)"
        }}
      >
        <div className={styles.newUpload}>
          <Button type="default" block>
            NEW UPLOAD
          </Button>
        </div>
        <Menu
          mode="inline"
          defaultSelectedKeys={[current]}
          style={{ borderRight: 0 }}
        >
          <Menu.Item key="mycontent" onClick={() => navigate("/mycontent")}>
            <span>
              <Badge
                status="processing"
                style={{ marginLeft: 4, marginRight: 5 }}
              />
              My Content
            </span>
          </Menu.Item>
          <Menu.Item key="purchased" onClick={() => navigate("/purchased")}>
            <span>
              <Badge
                status="processing"
                style={{ marginLeft: 4, marginRight: 5 }}
              />
              Purchased
            </span>
          </Menu.Item>
          <Menu.Item key="settings">
            <span>
              <Icon type="setting" />
              Settings
            </span>
          </Menu.Item>
        </Menu>
      </Sider>
    );
  }
}

export default SideMenu;
