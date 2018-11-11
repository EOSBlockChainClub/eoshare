import React, { Component } from "react";
import { Layout, Header, Sider } from "components/layouts";
import { Input } from "antd";
import Uploader from "components/uploader";
import classNames from "classnames";
import styles from "./upload.module.scss";

class UploadPage extends Component {
  state = {
    upload: true
  };
  render() {
    const { upload } = this.state;
    return (
      <Layout>
        <Header />
        <div className={styles.container}>
          <Sider />
          <div className={styles.contentContainer}>
            <Uploader />
            {upload && (
              <div className={styles.innerContainer}>
                <div
                  className={classNames(
                    styles.horizontal,
                    "col-xs-7",
                    styles.left
                  )}
                >
                  <h1 className={styles.title}>Select Category</h1>
                  <div
                    className={classNames(styles.horizontal, styles.category)}
                  >
                    <div className={classNames(styles.tag, styles.active)}>
                      MUSIC
                    </div>
                    <div className={styles.tag}>PHOTO</div>
                  </div>
                  <h1 className={styles.title}>Music Name</h1>
                  <Input
                    type="text"
                    placeholder="Music Name"
                    style={{ width: 400, marginTop: 12 }}
                  />
                  <h1 className={styles.title}>Artist Name</h1>
                  <Input
                    type="text"
                    placeholder="Artist Name"
                    style={{ width: 400, marginTop: 12 }}
                  />

                  <h1 className={styles.title}>Price</h1>
                  <Input
                    type="text"
                    placeholder="Price"
                    style={{ width: 400, marginTop: 12 }}
                  />
                </div>
                <div className={classNames(styles.thumbnail, "col-xs-5")} />
              </div>
            )}
            <h1 className={styles.title}>Previous Uploads</h1>
          </div>
        </div>
      </Layout>
    );
  }
}

export default UploadPage;
