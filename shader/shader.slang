static float2 position[3] = float2[](float2(0, -0.5), float2(0.5, 0.5), float2(-0.5, 0.5));

static float3 color[3] = float3[](float3(1, 0, 0), float3(0, 1, 0), float3(0, 0, 1));

struct VertexOutput {
  float3 color;
  float4 position : SV_Position;
};

[shader("vertex")]
VertexOutput vertexMain(uint vid: SV_VertexID) {
  VertexOutput vertexOutput;
  vertexOutput.position = float4(position[vid], 0, 1);
  vertexOutput.color = color[vid];
  return vertexOutput;
}

[shader("fragment")]
float4 fragmentMain(VertexOutput vertex) : SV_Target {
  return float4(vertex.color, 1);
}
