import React, { Component } from "react";
import { Button, Input, Icon, Avatar, Upload, message } from "antd";
import styles from "./header.module.scss";
import { Link, navigate } from "gatsby";

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
          <Upload
            showUploadList={false}
            onChange={info => {
              const status = info.file.status;
              if (status !== "uploading") {
                console.log(info.file, info.fileList);
              }
              if (status === "done") {
                navigate("/upload");
                message.success(
                  `${info.file.name} file uploaded successfully.`
                );
              } else if (status === "error") {
                message.error(`${info.file.name} file upload failed.`);
              }
            }}
          >
            <Button ghost type="primary">
              <span>
                <Icon type="upload" style={{ marginRight: 4 }} />
                UPLOAD
              </span>
            </Button>
          </Upload>
          <Avatar
            onClick={() => {
              navigate("/mycontent");
            }}
            style={{ cursor: "pointer" }}
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
