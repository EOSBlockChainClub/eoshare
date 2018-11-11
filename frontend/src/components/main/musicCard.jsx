import React, { Component } from "react";
import PropTypes from "prop-types";
import styles from "./musicCard.module.scss";
class MusicCard extends Component {
  render() {
    const { src, title, creator, price, onClick } = this.props;
    return (
      <div className={styles.container}>
        <div className={styles.thumnailContainer} onClick={onClick}>
          <img className={styles.image} src={src} alt={title} />
        </div>
        <h4 className={styles.title} onClick={onClick}>
          {title}
        </h4>
        <h5 className={styles.creator} onClick={onClick}>
          {creator}
        </h5>
        <h5 className={styles.price} onClick={onClick}>
          {price} SHARE
        </h5>
      </div>
    );
  }
}

MusicCard.propTypes = {
  src: PropTypes.string,
  className: PropTypes.string,
  title: PropTypes.string,
  creator: PropTypes.string,
  price: PropTypes.number
};

export default MusicCard;
