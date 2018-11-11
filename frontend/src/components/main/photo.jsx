import React, { Component } from "react";
import sectionStyles from "./section.module.scss";
import axios from "axios";
import PhotoCard from "./photoCard";
import shortid from "shortid";

const API_ENDPOINT = "http://localhost:9001";

class Photo extends Component {
  state = {
    photo: []
  };

  componentDidMount() {
    axios.get(`${API_ENDPOINT}/photo`).then(result => {
      if (result.data) {
        console.log(result.data);
        this.setState({ photo: result.data });
      }
    });
  }

  renderPhotoCard = () => {
    const { photo } = this.state;
    if (photo && photo.length > 0) {
      return photo.map(item => {
        return (
          <PhotoCard
            key={shortid.generate()}
            title={item.title}
            creator={item.creatorName}
            price={item.price}
            src={`${API_ENDPOINT}${item.thumbnail}`}
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
        <h1 className={sectionStyles.title}>NEW PHOTO</h1>
        <div className={sectionStyles.content}>{this.renderPhotoCard()}</div>
      </section>
    );
  }
}

export default Photo;
