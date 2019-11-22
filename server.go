package main

import (
	"encoding/base64"
	"fmt"
	"os"
	"strings"

	"github.com/gin-contrib/cors"
	"github.com/gin-gonic/gin"
)

const path = "./input/1.png"

type picture struct {
	PictData string `json:"pictData" form:"pictData"`
}

func main() {
	r := gin.Default()
	fmt.Println("try")
	config := cors.DefaultConfig()
	config.AllowAllOrigins = true
	// config.AllowOrigins = []string{"http://drawstick.ngrok.io/"}
	config.AllowHeaders = []string{"X-Token"}
	// config.AllowOrigins = []string{"http://127.0.0.1"}
	// config.AllowHeaders = []string{"X-Custom-Information"}
	r.Use(cors.New(config))
	r.POST("/v1/pict", getPicture)
	r.Run(":9080")
}

func getPicture(c *gin.Context) {
	c.JSON(200, gin.H{"Data": "1", "status": 200})
	fmt.Println("-----------------------------------------------")
	// data := c.Query("pictData")
	data := c.DefaultPostForm("pictData", ",")
	// fmt.Println(data)
	/*
		var info picture
		err := c.Bind(&info)
		if err != nil {
			fmt.Println("error")
		}
		fmt.Println(info)*/
	// data := info.PictData
	fmt.Println("-----------------------------------------------")
	pict := strings.Split(data, ",")
	// fmt.Println(pict[1])
	var enc = base64.StdEncoding
	pictdata, err := enc.DecodeString(pict[1])
	if err != nil {
		fmt.Println("decode error")
	}
	f, _ := os.OpenFile(path, os.O_RDWR|os.O_CREATE, os.ModePerm)
	defer f.Close()
	f.Write(pictdata)
	// c.JSON(200, gin.H{"Data": "1", "status": 200})
}
