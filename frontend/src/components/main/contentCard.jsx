import React, { Component } from "react";
import PropTypes from "prop-types";
import classNames from "classnames";
import { Tag } from "antd";
import styles from "./contentCard.module.scss";
class ContentCard extends Component {
  render() {
    const { className, usdt, title, creator, price } = this.props;
    return (
      <div className={classNames(styles.container, { [className]: className })}>
        <div className={styles.first}>
          <h4 className={styles.title}>{title}</h4>
          <h4 className={styles.price}>{price} SHARE</h4>
        </div>
        <div className={styles.second}>
          <h5 className={styles.creator}>{creator}</h5>
          <h5 className={styles.usdt}>{usdt}</h5>
        </div>
        <Tag className={styles.tags} color="#1890ff">
          MUSIC
        </Tag>
      </div>
    );
  }
}

ContentCard.propTypes = {
  className: PropTypes.string,
  title: PropTypes.string,
  creator: PropTypes.string,
  price: PropTypes.number,
  usdt: PropTypes.string
};

export default ContentCard;
