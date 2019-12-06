from http.server import HTTPServer
from http.server import BaseHTTPRequestHandler
import socketserver as SocketServer
from urllib.request import urlopen
from PIL import Image
import json
import os

class RequestHandler(BaseHTTPRequestHandler):
    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.end_headers()

    def do_GET(self):
        root = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'pyServer')
        #print(self.path)
        if self.path == '/':
            filename = root + '/index.html'
        else:
            filename = root + self.path
 
        self.send_response(200)
        if filename[-4:] == '.css':
            self.send_header('Content-type', 'text/css')
        elif filename[-5:] == '.json':
            self.send_header('Content-type', 'application/javascript')
        elif filename[-3:] == '.js':
            self.send_header('Content-type', 'application/javascript')
        elif filename[-4:] == '.ico':
            self.send_header('Content-type', 'image/x-icon')
        elif filename[-4:] == '.png':
            self.send_header('Content-type', 'image/png')
        else:
            self.send_header('Content-type', 'text/html')
        self.end_headers()
        with open(filename, 'rb') as fh:
            html = fh.read()
            #html = bytes(html, 'utf8')
            self.wfile.write(html)

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        data = json.loads(post_data)
        url = data['url']
        img = Image.open(urlopen(url))
        img.save("./input/1.png", "png")
        response = {
            'status':'SUCCESS',
            'data':'server got your post data',
            'result': '1'
        }
        self._set_headers()
        self.wfile.write(json.dumps(response))

def run():
    port = 13000
    print('Listening on localhost:%s' % port)
    
    server = HTTPServer(('', port), RequestHandler)
    server.serve_forever()

run()
'''
PORT = 10000
 
Handler = SimpleHTTPServer.SimpleHTTPRequestHandler
 
httpd = SocketServer.TCPServer(("", PORT), Handler)

print ("serving at port", PORT)
httpd.serve_forever()


url = "http://drawstickserver.ngrok.io/input/1.png"

'''

