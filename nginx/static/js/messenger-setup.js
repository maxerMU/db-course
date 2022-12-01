/* eslint-disable-next-line */
var messenger = {
  messageCache: [],
  queue: function () {
    this.messageCache.push(arguments);
  }
};

