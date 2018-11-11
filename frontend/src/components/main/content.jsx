import React, { Component } from "react";
import shortid from "shortid";
import { Tag } from "antd";
import ContentCard from "./contentCard";
import sectionStyles from "./section.module.scss";
import classNames from "classnames";
class Content extends Component {
  state = {
    content: [
      {
        title: "Emerald",
        price: 10.05,
        usdt: "$1.71",
        creator: "Gray"
      },
      {
        title: "Odessa",
        price: 21.41,
        usdt: "$4.66",
        creator: "Norris"
      },
      {
        title: "Highland",
        price: 14.14,
        usdt: "$2.88",
        creator: "Sykes"
      },
      {
        title: "Williston",
        price: 16.33,
        usdt: "$6.49",
        creator: "Jefferson"
      },
      {
        title: "Sunnyside",
        price: 27.96,
        usdt: "$7.43",
        creator: "Rodriguez"
      },
      {
        title: "Wyano",
        price: 13.6,
        usdt: "$1.18",
        creator: "Harvey"
      },
      {
        title: "Rosburg",
        price: 15.75,
        usdt: "$6.83",
        creator: "Bruce"
      },
      {
        title: "Tetherow",
        price: 12.93,
        usdt: "$0.59",
        creator: "Haney"
      },
      {
        title: "Vincent",
        price: 37,
        usdt: "$2.53",
        creator: "Solomon"
      },
      {
        title: "Loretto",
        price: 34.45,
        usdt: "$1.92",
        creator: "Best"
      },
      {
        title: "Frierson",
        price: 34.56,
        usdt: "$7.79",
        creator: "Harrison"
      },
      {
        title: "Unionville",
        price: 33.25,
        usdt: "$3.57",
        creator: "Prince"
      },
      {
        title: "Wilsonia",
        price: 25.57,
        usdt: "$0.57",
        creator: "Gomez"
      },
      {
        title: "Murillo",
        price: 39.9,
        usdt: "$4.02",
        creator: "Craft"
      },
      {
        title: "Fairmount",
        price: 37.14,
        usdt: "$0.50",
        creator: "Sears"
      },
      {
        title: "Tuskahoma",
        price: 38.02,
        usdt: "$2.04",
        creator: "Hicks"
      },
      {
        title: "Bodega",
        price: 28.1,
        usdt: "$0.85",
        creator: "Valentine"
      },
      {
        title: "Alfarata",
        price: 20.15,
        usdt: "$8.85",
        creator: "Walsh"
      }
    ]
  };

  renderContentCard = () => {
    const { content } = this.state;
    if (content && content.length > 0) {
      return content.map(item => {
        return (
          <ContentCard
            key={shortid.generate()}
            className="col-xs-4"
            title={item.title}
            creator={item.creator}
            price={item.price}
            usdt={item.usdt}
          />
        );
      });
    } else {
      return null;
    }
  };

  render() {
    return (
      <section className={sectionStyles.section}>
        <h1 className={sectionStyles.title}>CONTENT</h1>
        <div className={sectionStyles.tags}>
          <Tag color="blue">MUSIC</Tag>
          <Tag>PHOTO</Tag>
        </div>
        <div className={sectionStyles.sort}>
          <span>Most Downloaded</span>
          <span>Most Uploaded</span>
        </div>
        <div className={classNames(sectionStyles.total)}>
          {this.renderContentCard()}
        </div>
      </section>
    );
  }
}

export default Content;
