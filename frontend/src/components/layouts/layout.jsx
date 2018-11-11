import React from "react";
import Helmet from "react-helmet";
import { createMuiTheme, MuiThemeProvider } from "@material-ui/core/styles";
import styles from "./layout.module.scss";

const theme = createMuiTheme({
  typography: {
    htmlFontSize: "12px",
    fontSize: "12px"
  },
  palette: {
    primary: {
      light: "#7580ff",
      main: "#2f54eb",
      dark: "#002cb7",
      contrastText: "#fff"
    },
    secondary: {
      light: "#f0d4ff",
      main: "#bda3ef",
      dark: "#8c74bc",
      contrastText: "#151516"
    }
  },
  shape: {
    buttonBorderRadius: "100px",
    paperBorderRadius: "4px"
  }
});

const Layout = ({ title, children }) => (
  <>
    <Helmet>
      <title>{title}</title>
      <link href="/css/normalize.css" type="text/css" />
      <link
        href="https://fonts.googleapis.com/css?family=Roboto:400,700"
        rel="stylesheet"
      />
    </Helmet>
    <MuiThemeProvider theme={theme}>
      <div className={styles.layoutContainer}>{children}</div>
    </MuiThemeProvider>
  </>
);

Layout.defaultProps = {
  title: "EOShare"
};

export default Layout;
