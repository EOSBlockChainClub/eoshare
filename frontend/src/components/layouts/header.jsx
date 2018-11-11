import React, { Component } from "react";
import { Button, Input, Icon, Avatar } from "antd";
import styles from "./header.module.scss";
class Header extends Component {
  render() {
    return (
      <div className={styles.headerContainer}>
        <div className={styles.header}>
          <div className={styles.left}>
            <span className={styles.logo}>EOShare</span>
            <Input
              prefix={<Icon type="search" />}
              className={styles.search}
              placeholder="Search Creator Name or Content"
            />
          </div>
          <Button ghost type="primary">
            UPLOAD
          </Button>
          <Avatar
            src="/image/avatar.png"
            className={styles.avatar}
            size="default"
            icon="user"
          />
        </div>
      </div>
    );
  }
}

export default Header;
