const express = require("express");
const bodyParser = require("body-parser");
const morgan = require("morgan");
const cors = require("cors");

const app = express();

const photo = require("./photo");
const music = require("./music")

app.use(cors())

app.post("/create", (req,res)=>{
    //TODO create 
})

app.get("/music", (req,res, next)=>{
    return res.json(music)
})

app.get("/main", (req,res, next)=>{
    return res.json(music)
})

app.get("/photo", (req,res, next)=>{
    return res.json(photo)
})

app.use('/public',express.static('public'))
//GatsbyJS using [ 8000, 9000 ] Port.
app.listen(9001, ()=>{
    console.log("Listening on port 9001")
})
