import axios from 'axios'
import qs from 'qs'
import store from '../util/store'
// import bus from '../util/bus'

// const API_URL = 'http://localhost:9000/'
const API_URL = 'http://drawstickserver.ngrok.io'

let createApiAxios = function () {
  let myAxios = axios.create({
    baseURL: API_URL,
    timeout: 5000000,
    headers: {
      // 'Access-Control-Allow-Origin': '*',
      'X-Token': store.token
    },
    // crossDomain: true
  })

  // 请求拦截器，根据配置增加merchantOpenId参数
  myAxios.interceptors.request.use(function (config) {
    
    if (config.withMerchantOpenId) {
      let params = config.params || {}
      params.merchantOpenId = store.merchantInfo.merchantOpenId
      config.params = params
    }
    if (config.formData) {
      config.headers['Content-Type'] = 'application/x-www-form-urlencoded; charset=UTF-8'
      config.data = qs.stringify(config.data)
    }
    return config
  }, function (error) {
    return Promise.reject(error)
  })

  // 响应拦截器，根据错误消息，在bus上发起响应事件
  /*
  myAxios.interceptors.response.use(function (response) {
    if (response.status === 200 && response.data) {
      let data = response.data
      if (data && data.resCode === '0') {
        return Promise.resolve(response.data)
      } else {
        bus.$emit('apiError', data)
        console.log(`接口错误: ${data.resDesc}`)
        return Promise.reject(new Error(`接口错误: ${data.resDesc}`))
      }
    } else {
      bus.$emit('networkError', `网络错误: ${response.status}`)
      console.log(`网络错误: ${response.status}`)
      return Promise.reject(new Error(`网络错误: ${response.status}`))
    }
  }, function (error) {
    bus.$emit('networkError', `网络错误: ${error}`)
    console.log(`网络错误: ${error}`)
    return Promise.reject(error)
  })*/
  return myAxios
}

let apiAxios = createApiAxios()

export const uploadPict = (params) => {
  return apiAxios.get('v1/pict', {
    params: params
  })
}
