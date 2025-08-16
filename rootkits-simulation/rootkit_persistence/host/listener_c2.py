from http.server import HTTPServer, BaseHTTPRequestHandler
class H(BaseHTTPRequestHandler):
    def do_POST(self):
        n = int(self.headers.get('Content-Length',0)); b = self.rfile.read(n)
        print("From", self.client_address[0]); print(b.decode('utf-8','replace'))
        self.send_response(200); self.end_headers(); self.wfile.write(b"OK")
    def log_message(self, *a): pass
HTTPServer(("0.0.0.0",8080), H).serve_forever()

#python3 listener_c2.py