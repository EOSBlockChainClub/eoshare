import React, { Component } from "react";
import { Layout, Header } from "components/layouts";
import { Music } from "components/main/";
import styles from "./upload.module.scss";

class UploadPage extends Component {
  render() {
    return (
      <Layout>
        <Header />
        <div className={styles.innerContainer}>
        <div className={styles.horizontal}> 
          <div>
            <h1 className={styles.title}>Type</h1>
            <div className={styles.horizontal}>
              <div className={styles.tag}>MUSIC</div>
              <div className={styles.tag}>PHOTO</div>
            </div>
            <h1 className={styles.title}>Music Name</h1>
            <input type="text" placeholder="Music Name"/>
            <h1 className={styles.title}>Artist Name</h1>
            <input type="text" placeholder="Artist Name"/>

            <h1 className={styles.title}>Price</h1>
            <input type="text" placeholder="Price"/>
          </div>
        </div>
          <div class={styles.thumbnail}>
          </div>
        </div>

        <h1 className={styles.title}>Previous Uploads</h1>


      </Layout>
    );
  }
}

export default UploadPage;
