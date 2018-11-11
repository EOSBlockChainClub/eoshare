import React from "react";
import Helmet from "react-helmet";
import styles from "./layout.module.scss";

const Layout = ({ title, children }) => (
  <>
    <Helmet>
      <title>{title}</title>
      <link
        href="https://fonts.googleapis.com/css?family=Roboto:400,700"
        rel="stylesheet"
      />
      <link href="/css/normalize.css" rel="stylesheet" />
      <link href="/css/flexboxgrid.min.css" rel="stylesheet" />
    </Helmet>
    <div className={styles.layoutContainer}>{children}</div>
  </>
);

Layout.defaultProps = {
  title: "EOShare"
};

export default Layout;
