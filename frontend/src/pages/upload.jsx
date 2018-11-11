import React, { Component } from "react";
import { Layout, Header, Sider } from "components/layouts";
import { Input, Button, message } from "antd";
import { navigate } from "gatsby";
import classNames from "classnames";
import styles from "./upload.module.scss";
import axios from "axios";

const API_ENDPOINT = "http://localhost:9001";

class UploadPage extends Component {
  state = {
    loading: false
  };
  handleClick = () => {
    this.setState({ loading: true });
    axios.post(`${API_ENDPOINT}/create`).then(result => {
      message.success("Share Done!");
      navigate("/mycontent");
    });
  };
  render() {
    const { loading } = this.state;
    return (
      <Layout>
        <Header />
        <div className={styles.container}>
          <Sider />
          <div className={styles.contentContainer}>
            <div className={classNames(styles.topContainer)}>
              <span
                className={classNames("col-xs-12", styles.topRightContainer)}
              >
                <span style={{ color: "#ccc", marginRight: 10 }}>
                  Payment Account Name :{" "}
                  <strong style={{ color: "#1f1f1f" }}>dexeostestnt</strong>
                </span>
                <Button
                  loading={loading}
                  type="primary"
                  onClick={this.handleClick}
                >
                  SHARE!
                </Button>
              </span>
            </div>
            <div className={styles.innerContainer}>
              <div
                className={classNames(
                  styles.horizontal,
                  "col-xs-6",
                  styles.left
                )}
              >
                <h1 className={styles.title}>Select Category</h1>
                <div className={classNames(styles.horizontal, styles.category)}>
                  <div className={classNames(styles.tag)}>MUSIC</div>
                  <div className={classNames(styles.tag, styles.active)}>
                    PHOTO
                  </div>
                </div>
                <h1 className={styles.title} style={{ marginTop: 8 }}>
                  Photo Title
                </h1>
                <Input
                  type="text"
                  placeholder="Music Name"
                  style={{ width: 400, marginTop: 12 }}
                  value="Snow White"
                />
                <h1 className={styles.title} style={{ marginTop: 8 }}>
                  Artist Name
                </h1>
                <Input
                  type="text"
                  placeholder="Artist Name"
                  style={{ width: 400, marginTop: 12 }}
                  value="Eva Koepp"
                />

                <h1 className={styles.title} style={{ marginTop: 8 }}>
                  Price
                </h1>
                <Input
                  type="text"
                  placeholder="Price"
                  style={{ width: 400, marginTop: 12 }}
                  autoFocus
                />
              </div>
              <div className={classNames(styles.thumbnail, "col-xs-6")}>
                <img alt="snow white" src="http://localhost:9001/public/imagesix.jpg" />
              </div>
            </div>
          </div>
        </div>
      </Layout>
    );
  }
}

export default UploadPage;
