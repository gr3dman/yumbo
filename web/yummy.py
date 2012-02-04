import envoy
import web
from web.contrib.template import render_jinja

import config

URLS = (
    '/yummy/diagram/(.*)\.(.+)', 'Diagram',
    '/yummy/', 'Root'
)
DOT='/usr/local/bin/dot'
FORMATS = {
        'gif':      'image/gif',
        'jpeg':     'image/jpeg',
        'jpg':      'image/jpeg',
        'png':      'image/png',
        'svg':      'image/svg+xml'
}
JINJA = render_jinja(config.app_root + '/' + config.template_root, encoding = 'utf-8')

def draw(text, fmt):
    cmd = '%s | dot -T%s' % (config.yummydot_path, fmt)
    r = envoy.run(cmd, text)
    return r.std_out

class Root:
    def GET(self):
        return JINJA.index(diagram_base_url = config.diagram_base_url)

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
