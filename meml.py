import envoy
import web

URLS = (
    '/diagram/(.*)\.(.+)', 'Diagram'
)
MEMLDOT='/Users/Gareth/Source/meml/memldot'
FORMATS = {
        'gif':      'image/gif',
        'jpeg':     'image/jpeg',
        'jpg':      'image/jpeg',
        'png':      'image/png',
        'svg':      'image/svg+xml'
}

def draw(text, fmt):
    cmd = '%s | dot -T%s' % (MEMLDOT, fmt)
    r = envoy.run(cmd, text)
    return r.std_out

class Diagram:
    def GET(self, text, format):
        if format not in FORMATS:
            raise Exception('unknown format: ' + format)

        web.header('Content-Type', FORMATS[format])
        return draw(str(text), str(format))

app = web.application(URLS, globals())
if __name__ == '__main__':
    app.run()
else:
    application = app.wsgifunc()
