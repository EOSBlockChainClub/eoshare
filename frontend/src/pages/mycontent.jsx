import React, { Component } from "react";
import { Layout, Header, Sider } from "components/layouts";
import { Tag, Table, Button } from "antd";
import classNames from "classnames";
import styles from "./upload.module.scss";

const columns = [
  {
    title: "Index",
    dataIndex: "index",
    key: "index"
  },
  {
    title: "Type",
    dataIndex: "type",
    key: "type",
    render: type => <Tag color="#1890ff">{type.toUpperCase()}</Tag>
  },
  {
    title: "File Name",
    dataIndex: "title",
    key: "title"
  },
  {
    title: "Downloads",
    dataIndex: "downloads",
    key: "downloads"
  },
  {
    title: "Total Earning",
    dataIndex: "earning",
    key: "earning"
  },
  {
    title: "Seed",
    dataIndex: "seed",
    key: "seed"
  },
  {
    title: "Action",
    render: () => (
      <Button type="danger" ghost>
        Stop Seed
      </Button>
    )
  }
];

const dataSource = [
  {
    index: 1,
    type: "Photo",
    title: "Snow White",
    downloads: 0,
    earning: "0 SHARE",
    seed: 1
  },
  {
    index: 2,
    type: "Photo",
    title: "Sunset",
    downloads: 14,
    earning: "48 SHARE",
    seed: 4
  },
  {
    index: 3,
    type: "Photo",
    title: "Flower Girl",
    downloads: 182,
    earning: "2,049 SHARE",
    seed: 32
  }
];

class MycontentPage extends Component {
  render() {
    return (
      <Layout>
        <Header />
        <div className={styles.container}>
          <Sider current="mycontent" />
          <div className={styles.contentContainer}>
            <div className={classNames(styles.topContainer)}>
              <span
                style={{ fontSize: 24, fontWeight: "bold", color: "#151516" }}
              >
                My Content
              </span>
            </div>
            <div className={styles.innerContainer} style={{ paddingTop: 0 }}>
              <Table
                columns={columns}
                dataSource={dataSource}
                bordered
                style={{ width: "100%" }}
                locale={{
                  emptyText: "Your content will appear here"
                }}
              />
            </div>
          </div>
        </div>
      </Layout>
    );
  }
}

export default MycontentPage;
