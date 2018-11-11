import React, { Component } from "react";
import PropTypes from "prop-types";
import styles from "./photoCard.module.scss";
class PhotoCard extends Component {
  render() {
    const { src, className, title, creator, price } = this.props;
    return (
      <div className={styles.container}>
        <div className={styles.thumnailContainer}>
          <img className={styles.image} src={src} />
        </div>
        <h4 className={styles.title}>{title}</h4>
        <h5 className={styles.creator}>{creator}</h5>
        <h5 className={styles.price}>{price} SHARE</h5>
      </div>
    );
  }
}

PhotoCard.propTypes = {
  src: PropTypes.string,
  className: PropTypes.string,
  title: PropTypes.string,
  creator: PropTypes.string,
  price: PropTypes.number
};

export default PhotoCard;
