import React, { Component } from "react";
import { Button, Input, Icon, Avatar } from "antd";
import styles from "./header.module.scss";
import { Link } from "gatsby";

class Header extends Component {
  render() {
    return (
      <div className={styles.headerContainer}>
        <div className={styles.header}>
          <div className={styles.left}>
            <Link to="/">
              <span className={styles.logo}>EOShare</span>
            </Link>
            <Input
              prefix={<Icon type="search" />}
              className={styles.search}
              placeholder="Search Creator Name or Content"
            />
          </div>
          <Link to="/upload">
            <Button ghost type="primary">
              <span>
                <Icon type="upload" style={{ marginRight: 4 }} />
                UPLOAD
              </span>
            </Button>
          </Link>
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
