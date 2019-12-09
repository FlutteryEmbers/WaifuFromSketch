import Home from './components/draw.vue'
import Result from './components/result.vue'
const routers = [
  {
    path: '/home',
    name: 'home',
    component: Home
  },{
    path: '/',
    component: Home
  },{
      path: '/result',
      component: Result
  }
]
export default routers