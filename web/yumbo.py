import subprocess
import web
from web.contrib.template import render_jinja

import config

URLS = (
    '/yumbo/diagram/(.*)\.(.+)', 'Diagram',
    '/yumbo/', 'Root'
)
FORMATS = {
        'gif':      'image/gif',
        'jpeg':     'image/jpeg',
        'jpg':      'image/jpeg',
        'png':      'image/png',
        'svg':      'image/svg+xml'
}
JINJA = render_jinja(config.app_root + '/' + config.template_root, encoding = 'utf-8')

def draw(text, fmt):
    echo = subprocess.Popen(['echo', text], stdout=subprocess.PIPE)
    yumbodot = subprocess.Popen(config.yumbodot_path,
                                stdin=echo.stdout, stderr=subprocess.PIPE,
                                stdout=subprocess.PIPE)
    dot = subprocess.Popen([config.dot_path, '-T', fmt],
                           stdin=yumbodot.stdout, stderr=subprocess.PIPE,
                           stdout=subprocess.PIPE)
    (out, derr) = dot.communicate()
    (_, yderr) = yumbodot.communicate()
    if yumbodot.returncode != 0:
        raise Exception(yderr)
    elif dot.returncode != 0:
        raise Exception(derr)
    else:
        return out

def draw_error(error):
    script = '''new
size 400,300
fill 0,0,255,255,255

string 0,0,0,20,20,small,a wild error appeared:
string 0,0,0,40,40,small,%s''' % error
    echo = subprocess.Popen(['echo', script], stdout=subprocess.PIPE)
    fly = subprocess.Popen([config.fly_path], stdin=echo.stdout,
                            stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    (out, err) = fly.communicate()
    if fly.returncode == 0:
        return out
    else:
        raise Exception('fly return code was %d, stderr is %s' %
                (fly.returncode, fly.stderr))


class Root:
    def GET(self):
        return JINJA.index(diagram_base_url = config.diagram_base_url)

class Diagram:
    def GET(self, text, format):
        try:
            if format not in FORMATS:
                raise Exception('unknown format: ' + format)

            web.header('Content-Type', FORMATS[format])
            return draw(str(text), str(format))
        except Exception as err:
            try:
                web.header('Content-Type', FORMATS['png'])
                return draw_error(err)
            except Exception as err:
                web.header('Content-Type', 'text/plain')
                return err


app = web.application(URLS, globals())
if __name__ == '__main__':
    app.run()
else:
    application = app.wsgifunc()
