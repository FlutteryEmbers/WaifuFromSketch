/**
 * Created by wang on 2017/10/25.
 */
import Vue from 'vue'
import bus from './bus'

export default new Vue({
  data: {
    userInfo: {},
    merchantInfo: {},
    token: ''
  },
  methods: {
    setToken: function (token) {
      if (token) {
        let storedToken = localStorage.getItem('hudson.community.token')
        this.token = token
        if (token !== storedToken) {
          localStorage.setItem('hudson.community.token', token)
        }
        bus.$emit('setToken', token)
      } else {
        // 退出登录
        this.token = ''
        localStorage.removeItem('hudson.community.token', '')
      }
    },
    setMerchantInfo: function (merchantInfo) {
      this.merchantInfo = merchantInfo
      localStorage.setItem('hudson.community.selectMerchantOpenId', this.merchantInfo.merchantOpenId)
      bus.$emit('setMerchantInfo', merchantInfo)
    },
    setUserInfo: function (userInfo) {
      this.userInfo = userInfo
      bus.$emit('setUserInfo', userInfo)
    },
    hasRole (role) {
      // console.log(role)
      // console.log(this.merchantInfo)
      if (!this.merchantInfo || !this.merchantInfo.role) return false
      if (role === 1001) return this.userInfo.isPlatformManager === 0
      for (let x of this.merchantInfo.role) {
        if (role === x) return true
      }
      return false
    },
    hasMod (mod) {
      // debugger
      if (!mod) return true
      if (!this.merchantInfo || !this.merchantInfo.merchantOpenId) return false
      if (mod === 'bigData') {
        return (this.merchantInfo.merchantOpenId === 'vybp6LzklDm9sWoby1lOnw' || this.merchantInfo.merchantOpenId === 'undgItb58v3qydbQfHZLmQ')
      }
      if (this.merchantInfo.merchantOpenId === 'nKBNoWo9rc-GvGOoQvZPrg') {
        let modEnabled = ['fire', 'smoke', 'water']
        return modEnabled.includes(mod)
      }
      return true
    }
  },
  created: function () {
    // 读取token
    let storedToken = localStorage.getItem('hudson.community.token')
    if (storedToken) this.setToken(storedToken)
    // 读取merchantOpenId
    let selectMerchantOpenId = localStorage.getItem(
      'hudson.community.selectMerchantOpenId')
    let merchantInfo
    if (selectMerchantOpenId) {
      merchantInfo = {
        merchantOpenId: selectMerchantOpenId
      }
      this.setMerchantInfo(merchantInfo)
    }
  }
})
