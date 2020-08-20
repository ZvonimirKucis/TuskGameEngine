#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 LightPos;
in vec2 TexCoords;

in vec3 TangentLightPos;
in vec3 TangentFragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

uniform vec3 lightColor;

void main() {
     vec3 normal = texture(texture_normal1, TexCoords).rgb;
     normal = normalize(normal * 2.0 - 1.0); 

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * texture(texture_diffuse1, TexCoords).rgb;    
    
     // diffuse 
    float diffuseStrength = 1.0;
    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * diff * texture(texture_diffuse1, TexCoords).rgb;
    
    // specular
    float specularStrength = 0.8;
    vec3 viewDir = normalize(-TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * texture(texture_specular1, TexCoords).rgb; 
    
    float alpha = texture(texture_diffuse1, TexCoords).a;
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, alpha);
}