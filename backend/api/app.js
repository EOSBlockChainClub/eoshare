const express = require("express");
const bodyParser = require("body-parser");
const morgan = require("morgan");
const cors = require("cors");
const EOSJS = require("eosjs");
const app = express();
const binaryen = require('binaryen');
const shortid = require("shortid");

const photo = require("./photo");
const music = require("./music")

const httpEndpoint = ['http://dev.cryptolions.io:38888'];
const chainId = '038f4b0fc8ff18a4f0842a8f0564611f6e96e8535901dd45e43ac8691a1c4dca';
const defaultPrivateKey = "5JcGkzTK3nsWfWJhkw2QnocjkAezSGsfZvNtmBPDvLThPpZrxmZ"; // useraaaaaaaa

const keyProvider = [defaultPrivateKey];
const point = httpEndpoint[(Math.floor(Math.random() * httpEndpoint.length))];
const eos =  EOSJS({httpEndpoint: point, chainId, keyProvider, binaryen})

app.use(cors())

app.get("/music", (req,res, next)=>{
    return res.json(music)
})

app.get("/main", (req,res, next)=>{
    return res.json(music)
})

app.get("/photo", (req,res, next)=>{
    return res.json(photo)
})

//All of this should be at the front, hardcoding for demo
//name owner, string artist_name, string content_title, uint8_t content_type, asset price, string storage_uri, bool status
app.post("/create",(req,res,next)=>{
    console.log("create called")
    eos.transaction({
        actions: [{
            account: 'eoshareagent',
            name: 'upload',
            authorization: [{
              actor: 'dexeostestnt',
              permission: 'active',
            }],
            data: {
              owner: 'dexeostestnt',
              artist_name:"Snow White",
              content_title:"Eva Koepp",
              content_type: 1,
              price:`1.0000 SHARE`,
              storage_uri:`ipfs/${shortid.generate()}jH7E9kSBjsdfsdff${shortid.generate()}/`,
              status:1,
            },
          }]
    }).then((result)=>{
        return res.json({success:true})
    }).catch(err=>{
        return res.status(500).send(err)
    })
})

app.use('/public',express.static('public'))
//GatsbyJS using [ 8000, 9000 ] Port.
app.listen(9001, ()=>{
    console.log("Listening on port 9001")
})
