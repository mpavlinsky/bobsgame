
#ifdef GL_ES
precision mediump float;
#endif

//#extension GL_OES_standard_derivatives : enable
// glsl mixed by gigatron ;
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

float h00(float x) { return 2.*x*x*x - 3.*x*x + 1.; }
float h10(float x) { return x*x*x - 2.*x*x + x; }
float h01(float x) { return 3.*x*x - 2.*x*x*x; }
float h11(float x) { return x*x*x - x*x; }

float Hermite(float p0, float p1, float m0, float m1, float x)
{
    return p0*h00(x) + m0*h10(x) + p1*h01(x) + m1*h11(x);
}

void main()
{
    vec2 uv = gl_FragCoord.xy/ resolution.xy;

    float a = sin(time/20.0 * 1.0)*0.5 + 0.5;
    float b = sin(time/10.0 * 1.5)*0.5 + 0.5;
    float c = sin(time/20.0 * 2.0)*0.5 + 0.5;
    float d = sin(time/10.0 * 2.5)*0.5 + 0.5;

    float y0 = mix(a, b, uv.x);
    float y1 = mix(c, d, uv.x);
    float x0 = mix(a, c, uv.y);
    float x1 = mix(b, d, uv.y);

    uv.x = Hermite(0., 1., 3.*x0, 3.*x1, uv.x);
    uv.y = Hermite(0., 1., 3.*y0, 3.*y1, uv.y);


     vec3 color=vec3(-1.);



    float gradient,angle,fade = 0.0;

 // Thx to Zavie, Optimus !



    float u,v,z;

    vec2 coord = mod(uv,1.0);
    vec2 centered_coord = coord - vec2(0.5);
    float dist_from_center = length(centered_coord);



    float dist_from_center_y = length(centered_coord.y);
            u = 8.0/dist_from_center_y + 16.0*time;
            v = (16.0/dist_from_center_y)* centered_coord.x + sin(time) * 8.0;

            fade = dist_from_center_y * 2.0;
            gradient = ((1.0 - pow(sin(u) + 1.0, 0.1)) + (1.0 - pow(sin(v) + 0.0, 0.2))) * fade;
            color = vec3(gradient/2.,gradient*2.,gradient*4.);


      gl_FragColor = vec4(color,1.0);
}
