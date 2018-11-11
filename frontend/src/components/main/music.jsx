import React, { Component } from "react";
import sectionStyles from "./section.module.scss";
import axios from "axios";
import MusicCard from "./musicCard";
import shortid from "shortid";

const API_ENDPOINT = "http://localhost:9001";

class Music extends Component {
  state = {
    music: []
  };

  componentDidMount() {
    axios.get(`${API_ENDPOINT}/main`).then(result => {
      if (result.data) {
        console.log(result.data);
        this.setState({ music: result.data });
      }
    });
  }

  renderMusicCard = () => {
    const { music } = this.state;
    if (music && music.length > 0) {
      return music.map(item => {
        return (
          <MusicCard
            key={shortid.generate()}
            title={item.musicName}
            creator={item.creatorName}
            price={item.price}
            src={`${API_ENDPOINT}/public${item.thumbnail}`}
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
        <h1 className={sectionStyles.title}>NEW MUSIC</h1>
        <div className={sectionStyles.content}>{this.renderMusicCard()}</div>
      </section>
    );
  }
}

export default Music;
