import React, { Component } from "react";
import { Upload, Icon, message } from "antd";
const Dragger = Upload.Dragger;

class Uploader extends Component {
  render() {
    const props = {
      name: "file",
      multiple: true,
      onChange(info) {
        const status = info.file.status;
        if (status !== "uploading") {
          console.log(info.file, info.fileList);
        }
        if (status === "done") {
          message.success(`${info.file.name} file uploaded successfully.`);
        } else if (status === "error") {
          message.error(`${info.file.name} file upload failed.`);
        }
      }
    };

    return (
      <div style={{ display: "flex", width: "100%", padding: 40 }}>
        <Dragger {...props} style={{ padding: 20 }}>
          <p className="ant-upload-drag-icon">
            <Icon type="inbox" />
          </p>
          <p className="ant-upload-text">
            Click or drag file to this area to upload
          </p>
          <p className="ant-upload-hint">
            Support for a single or bulk upload. Strictly prohibit from
            uploading company data or other band files
          </p>
        </Dragger>
      </div>
    );
  }
}

export default Uploader;
