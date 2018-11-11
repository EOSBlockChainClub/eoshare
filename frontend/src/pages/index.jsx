import React, { Component } from "react";
import { Layout, Header } from "components/layouts";
import { Music, Photo, Content } from "components/main/";
import styles from "./index.module.scss";
class IndexPage extends Component {
  render() {
    return (
      <Layout>
        <Header />
        <div className={styles.container}>
          {/*Hello EOS Hackathon!*/}
          <Music />
          <Photo />
          <Content />
        </div>
      </Layout>
    );
  }
}

export default IndexPage;
