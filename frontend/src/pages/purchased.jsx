import React, { Component } from "react";
import { Layout, Header, Sider } from "components/layouts";
import { Table, Button, Progress, Tag } from "antd";
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
    title: "Price",
    dataIndex: "price",
    key: "price",
    render: price => <span>{price} SHARE</span>
  },
  {
    title: "Download",
    dataIndex: "download",
    key: "download",
    render: download => <Progress percent={download} />
  },
  {
    title: "Upload",
    dataIndex: "upload",
    key: "upload"
  },
  {
    title: "Seed Earning",
    dataIndex: "earning",
    key: "earning"
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
    type: "Music",
    title: "Yuna",
    price: 3,
    download: 13,
    upload: "14/kb",
    earning: "10 SHARE"
  },
  {
    index: 2,
    title: "Culture",
    type: "Music",
    price: 9,
    download: 100,
    upload: "65mb",
    earning: "37 SHARE"
  },
  {
    index: 3,
    title: "Ghost",
    type: "Music",
    price: 6,
    download: 100,
    upload: "22mb",
    earning: "78 SHARE"
  },
  {
    index: 4,
    title: "Dear",
    type: "Photo",

    price: 67,
    download: 100,
    upload: "14mb",
    earning: "197 SHARE"
  },
  {
    index: 5,
    title: "Awake",
    type: "Music",
    price: 4,
    download: 100,
    upload: "40mb",
    earning: "48 SHARE"
  },
  {
    index: 1,
    type: "Photo",
    title: "Clear Sky",
    price: 898,
    download: 100,
    upload: "102mb",
    earning: "480 SHARE"
  }
];

class PurchasedPage extends Component {
  render() {
    return (
      <Layout>
        <Header />
        <div className={styles.container}>
          <Sider current="purchased" />
          <div className={styles.contentContainer}>
            <div className={classNames(styles.topContainer)}>
              <span
                style={{ fontSize: 24, fontWeight: "bold", color: "#151516" }}
              >
                Purchased
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

export default PurchasedPage;
