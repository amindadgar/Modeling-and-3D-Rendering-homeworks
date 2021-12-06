#version 130 
 in vec4 points; 
 in vec4 Vcolors; 
 out vec4 color; 
 uniform vec3 theta;
 void main() 
 { 
	vec3 angles = radians( theta );
	vec3 c = cos( angles );
	vec3 s = sin( angles ); 
	mat4 rx = mat4( 1.0, 0.0, 0.0, 0.0,
					0.0, c.x, s.x, 0.0,
					0.0,-s.x, c.x, 0.0,
					0.0, 0.0, 0.0, 1.0 );
 	mat4 ry = mat4( c.y, 0.0,-s.y, 0.0,
 					0.0, 1.0, 0.0, 0.0,
 					s.y, 0.0, c.y, 0.0,
 					0.0, 0.0, 0.0, 1.0 );
 	mat4 rz = mat4( c.z,s.z, 0.0, 0.0,
 					-s.z, c.z, 0.0, 0.0,
 					0.0, 0.0, 1.0, 0.0,
 					0.0, 0.0, 0.0, 1.0 );
 	mat4 T  = mat4( 1.0, 0.0, 0.0, 0.0,	
 					0.0, 1.0, 0.0, 0.0,
 					0.0, 0.0, 1.0, 0.0,
 					0.0, 0.0, 0.0, 1.0 ); 
 	 
 	gl_Position = T * rz * ry * rx * points;
 	color=Vcolors;
 }