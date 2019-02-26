import axios from "axios";

// 基础配置
const Axios = axios.create({
  baseURL: "",
  timeout: 5000,
  withCredentials: true
});
// 拦截request
Axios.interceptors.request.use(
  config => {
    // ...
    return config;
  },
  error => {
    return Promise.reject(error);
  }
);
// 拦截response
Axios.interceptors.response.use(
  res => {
    // ...
    return res;
  },
  error => {
    return Promise.reject(error);
  }
);

export default Axios;
