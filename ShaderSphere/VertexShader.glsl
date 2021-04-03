#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_textureCoord;
layout(location = 3) in vec3 v_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;
uniform vec3 object_color;


// TODO: output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_textureCoord;
out vec3 frag_color;

uint hash( uint x ) {
    x += ( x << 10u );
    x ^= ( x >>  6u );
    x += ( x <<  3u );
    x ^= ( x >> 11u );
    x += ( x << 15u );
    return x;
}

uint hash( uvec4 v ) { return hash( v.x ^ hash(v.y) ^ hash(v.z) ^ hash(v.w) ); }

float floatConstruct( uint m ) {
    const uint ieeeMantissa = 0x007FFFFFu; // binary32 mantissa bitmask
    const uint ieeeOne      = 0x3F800000u; // 1.0 in IEEE binary32

    m &= ieeeMantissa;                     // Keep only mantissa bits (fractional part)
    m |= ieeeOne;                          // Add fractional part to 1.0

    float  f = uintBitsToFloat( m );       // Range [1:2]
    return f - 1.0;                        // Range [0:1]

}

float random( vec4  v ) { return floatConstruct(hash(floatBitsToUint(v))); }



void main()
{
	vec4 inputs = vec4( v_position.xyz, Time ); // Spatial and temporal inputs
    float rand  = random( inputs );              // Random per-pixel value

    frag_color   = object_color + vec3( 0.3, 0, - abs((sin(2 * Time) * rand )));

    vec3 newPosition = v_position + v_position * abs(sin(Time)) * 0.5 * rand;
	gl_Position = Projection * View * Model * vec4(newPosition, 1.0);
}
