import React from "react";
import Helmet from "react-helmet";
import styles from "./layout.module.scss";

const Layout = ({ title, children }) => (
  <>
    <Helmet>
      <title>{title}</title>
      <link href="/css/normalize.css" type="text/css" />
    </Helmet>
    <div className={styles.layoutContainer}>{children}</div>
  </>
);

Layout.defaultProps = {
  title: "EOShare"
};

export default Layout;
