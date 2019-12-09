import Vue from 'vue'
import VueRouter from 'vue-router'
import App from './App.vue'
import MuseUI from 'muse-ui'
import routers from './routers'
import 'muse-ui/dist/muse-ui.css'
import 'muse-ui/dist/theme-light.min.css'
Vue.config.productionTip = false
Vue.use(MuseUI)
Vue.use(VueRouter)
const router = new VueRouter({
  mode: 'history',
  routes: routers
})
new Vue({
  el: '#app',
  router,
  render: h => h(App),
}).$mount('#app')
