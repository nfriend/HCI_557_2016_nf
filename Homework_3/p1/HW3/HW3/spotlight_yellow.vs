#version 330 core

// The vertex buffer input                                    
in vec3 in_Color; 
in vec3 in_Position; 
in vec3 in_Normal;  

// Transformations for the projections
uniform mat4 projectionMatrixBox;
uniform mat4 viewMatrixBox;
uniform mat4 modelMatrixBox;
uniform mat4 inverseViewMatrix;

// The material parameters 
uniform vec3 diffuse_color;                                        
uniform vec3 ambient_color;                                         
uniform vec3 specular_color;   

// Position of the light sources
uniform vec4 light_position_1;   
uniform vec4 light_position_2;   

// New parameters for the spotlight
uniform float cone_angle_1;
uniform float cone_angle_2;
uniform vec3 cone_direction_1;
uniform vec3 cone_direction_2;

// The intensity values for the reflection equations
uniform float diffuse_intensity_1;                                          
uniform float diffuse_intensity_2;                                          
uniform float ambient_intensity_1;
uniform float ambient_intensity_2;
uniform float specular_intensity_1;                                       
uniform float specular_intensity_2;                                       
uniform float attenuationCoefficient_1;                                    
uniform float attenuationCoefficient_2;                                    
uniform float shininess;    

                                              



// The output color
out vec3 pass_Color;                                            
                                                                 
float smoothstep(float edge0, float edge1, float x)
{
	// Scale, bias and saturate x to 0..1 range
	x = clamp((x - edge0)/(edge1 - edge0), 0.0, 1.0);
	// Evaluate polynomial
	return x*x*(3 - 2*x);
}
                                          
                                                                                                                               
void main(void)                                                 
{                                                               
	vec3 normal = normalize(in_Normal);                                                                   
    vec4 transformedNormal = normalize(transpose(inverse( modelMatrixBox)) * vec4( normal, 1.0 ));
    
    vec4 surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);
                                                                                                       
    vec4 surface_to_light =   normalize( light_position_1 -  surfacePostion );                      
                                                                                                            
    // Diffuse color                                                                                          
    float diffuse_coefficient = max( dot(transformedNormal, surface_to_light), 0.0);
    vec3 out_diffuse_color = diffuse_color  * diffuse_coefficient * diffuse_intensity_1;                        
                                                                                                              
    // Ambient color                                                                                         
    vec3 out_ambient_color = vec3(ambient_color) * ambient_intensity_1;                                        
                                                                                                             
    // Specular color                                                                                        
    vec3 incidenceVector = -surface_to_light.xyz;
    vec3 reflectionVector = reflect(incidenceVector, normal.xyz);
    
    vec3 cameraPosition = vec3( inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);
    
    float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
    float specular_coefficient = pow(cosAngle, shininess);                                                     
    vec3 out_specular_color = specular_color * specular_coefficient * specular_intensity_1;                    
  
	
	//attenuation
    float distanceToLight = length(light_position_1.xyz - surfacePostion.xyz);
    float attenuation_1 = 1.0 / (1.0 + attenuationCoefficient_1 * pow(distanceToLight, 2));
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////        
    // Spotlight
    // 1. Normalize the cone direction
    vec3 cone_direction_norm = normalize(cone_direction_1); 
    
    // 2. Calculate the ray direction. We already calculated the surface to light direction.
    // 	  All what we need to do is to inverse this value
    vec3 ray_direction = -surface_to_light.xyz;   
    
    // 3. Calculate the angle between light and surface using the dot product again. 
    //    To simplify our understanding, we use the degrees
    float light_to_surface_angle = degrees(acos(dot(ray_direction, cone_direction_norm))) ; 
    
	attenuation_1 = smoothstep(-3, 3, cone_angle_1 - light_to_surface_angle);
	
	
	// Calculate the linear color
	vec3 linearColor = out_ambient_color  + attenuation_1 * ( out_diffuse_color + out_specular_color);  
   
	// Gamma correction	
	vec3 gamma = vec3(1.0/2.2);
	vec3 finalColor_1 = pow(linearColor, gamma);











	normal = normalize(in_Normal);                                                                   
    transformedNormal = normalize(transpose(inverse( modelMatrixBox)) * vec4( normal, 1.0 ));
    
    surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);
                                                                                                       
    surface_to_light =   normalize( light_position_2 -  surfacePostion );                      
                                                                                                            
    // Diffuse color                                                                                          
    diffuse_coefficient = max( dot(transformedNormal, surface_to_light), 0.0);
    out_diffuse_color = diffuse_color  * diffuse_coefficient * diffuse_intensity_2;                        
                                                                                                              
    // Ambient color                                                                                         
    out_ambient_color = vec3(ambient_color) * ambient_intensity_2;                                        
                                                                                                             
    // Specular color                                                                                        
    incidenceVector = -surface_to_light.xyz;
    reflectionVector = reflect(incidenceVector, normal.xyz);
    
    cameraPosition = vec3( inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);
    surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);
    
    cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
    specular_coefficient = pow(cosAngle, shininess);                                                     
    out_specular_color = specular_color * specular_coefficient * specular_intensity_2;                    
  
	
	//attenuation
    distanceToLight = length(light_position_2.xyz - surfacePostion.xyz);
    float attenuation_2 = 1.0 / (1.0 + attenuationCoefficient_2 * pow(distanceToLight, 2));
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////        
    // Spotlight
    // 1. Normalize the cone direction
    cone_direction_norm = normalize(cone_direction_2); 
    
    // 2. Calculate the ray direction. We already calculated the surface to light direction.
    // 	  All what we need to do is to inverse this value
    ray_direction = -surface_to_light.xyz;   
    
    // 3. Calculate the angle between light and surface using the dot product again. 
    //    To simplify our understanding, we use the degrees
    light_to_surface_angle = degrees(acos(dot(ray_direction, cone_direction_norm))) ; 
    
	attenuation_2 = smoothstep(-3, 3, cone_angle_2 - light_to_surface_angle);
	
	
	// Calculate the linear color
	linearColor = out_ambient_color  + attenuation_2 * ( out_diffuse_color + out_specular_color);  
   
	// Gamma correction	
	gamma = vec3(1.0/2.2);
	vec3 finalColor_2 = pow(linearColor, gamma);












	
	// Pass the color 
	pass_Color =  finalColor_1 + finalColor_2;
	
	// Passes the projected position to the fragment shader / rasterization process. 
    gl_Position = projectionMatrixBox * viewMatrixBox * modelMatrixBox * vec4(in_Position, 1.0);                                                                                                                   
                          
}                                                                                                            