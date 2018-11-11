import React, { Component } from "react";
import Button from "@material-ui/core/Button";
import styles from "./header.module.scss";
class Header extends Component {
  render() {
    return (
      <div className={styles.headerContainer}>
        <div className={styles.header}>
          <span>EOShare</span>
          <Button>UPLOAD</Button>
        </div>
      </div>
    );
  }
}

export default Header;
