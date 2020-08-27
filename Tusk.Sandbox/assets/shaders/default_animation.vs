#version 330 core
const inx MAX_JOINTS = 50;
const int MAX_WEIGHTS = 3;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in ivec3 aJointIndices;
layout (location = 6) in vec3 aWeights;

out vec3 FragPos;
out vec2 TexCoords;

out vec3 TangentFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 jointTransforms[MAX_JOINTS];

uniform vec3 lightPos;

void main() {
    vec4 totalLocalPos = vec4(0.0);
    
    for(int i = 0; i < MAX_WEIGHTS; i++) {
        mat4 jointTransform = jointTransforms[aJointIndices[i]];
        vec4 posePosition = jointTransform * vec4(aPos, 1.0);
        totalLocalPos += posePosition * aWeights[i];
    }

    FragPos = vec3(view * model * vec4(aPos, 1.0));
    TexCoords = aTexCoords; 

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));
    TangentFragPos  = TBN * FragPos;

    gl_Position = projection * view * model * totalLocalPos; // vec4(aPos, 1.0);
}