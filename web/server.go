package main

import (
	"bytes"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"net/http"
	"os"
	"strings"

	"github.com/gin-contrib/cors"
	"github.com/gin-gonic/gin"
)

const path = "./input/1.png"
const pyServer = "http://127.0.0.1:13000/"
const imageURL = "http://drawstickserver.ngrok.io/input/1.png"

type picture struct {
	PictData string `json:"pictData" form:"pictData"`
}

func main() {
	r := gin.Default()
	fmt.Println("try")
	config := cors.DefaultConfig()
	config.AllowAllOrigins = true
	config.AllowHeaders = []string{"X-Token"}
	r.Use(cors.New(config))
	r.POST("/v1/pict", getPicture)
	r.Static("/input", "./input")
	r.Static("/output", "./output")
	r.StaticFile("/result.html", "./index.html")
	r.Run(":9080")
}

func getPicture(c *gin.Context) {
	data := c.DefaultPostForm("pictData", ",")
	pict := strings.Split(data, ",")
	var enc = base64.StdEncoding
	pictdata, err := enc.DecodeString(pict[1])
	if err != nil {
		fmt.Println("decode error")
	}
	f, _ := os.OpenFile(path, os.O_RDWR|os.O_CREATE, os.ModePerm)
	defer f.Close()
	f.Write(pictdata)
	values := map[string]string{"url": imageURL}
	jsonValue, _ := json.Marshal(values)
	resp, err := http.Post(pyServer, "application/json", bytes.NewBuffer(jsonValue))
	if err != nil {
		fmt.Println("error")
		return
	}
	fmt.Println(resp)
	c.JSON(200, gin.H{"Data": "1", "status": 200})
}
