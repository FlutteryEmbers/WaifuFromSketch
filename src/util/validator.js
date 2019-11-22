export const mobileValidator = (rule, value, callback) => {
  if (/^1\d{10}$/.test(value)) {
    return callback()
  } else {
    return callback(new Error('手机号格式不正确'))
  }
}
