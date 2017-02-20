#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 resolution;

float noise22(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9,78.2))) * 43758.5);
}

float last_a = 0.0;

float wave(vec2 p, int depth, int scale, float amp, float freq, float wh, float move, vec2 modif)
{
 
  float a = 0.0;
  float fi            = float(depth);
  float div_height    = 18.0;
  float m_div         = 200.0/fi;    
  float m_order_h     = fi * 0.09; 
  float m_height      = wh - m_order_h;
  float m_paralax     = fi*10.0 / float(scale);
  float m_scale       = fi / div_height;
  float m_m_var       = 90.0*fi;
  float m_wave        = amp*0.002*cos(move + m_paralax + p.x*freq);
  float s             = floor(m_div*(p.x) + m_m_var + move);
  float ns            = noise22(vec2(s) + modif);
  
  if (p.y < ns*m_scale + m_height + m_wave)
  {
      a = fi/float(scale);
      last_a = a;
      return a;
  }

   return last_a;
}

void main()
{
    vec2 p = gl_FragCoord.xy / resolution;
    float a = 0.0;
    const int steps = 6;
	
    for(int i = 1; i < steps; i++)
    {
      a = wave(p, i, steps, 0.125, float(steps), 0.7, time * (10.0 + 0.001 * cos(time*0.5)), vec2(1.0,1.0) );
    }
  
    gl_FragColor = vec4(vec3(a*p.x, a*p.y, a * (1.0 - p.x) ), 1.0 );
}