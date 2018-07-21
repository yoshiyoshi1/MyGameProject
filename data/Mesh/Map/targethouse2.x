xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 20;
 -0.80000;0.00000;0.40000;,
 -0.80000;0.00000;0.80000;,
 -0.80000;2.00000;0.80000;,
 -0.80000;2.25000;0.40000;,
 0.80000;-0.00000;0.80000;,
 0.80000;2.00000;0.80000;,
 0.80000;0.00000;-0.40000;,
 0.80000;0.00000;-0.80000;,
 0.80000;2.00000;-0.80000;,
 0.80000;2.25000;-0.40000;,
 -0.80000;0.00000;-0.80000;,
 -0.80000;2.00000;-0.80000;,
 -0.80000;0.00000;-0.40000;,
 -0.80000;2.25000;-0.40000;,
 0.80000;2.25000;0.40000;,
 0.80000;2.00000;0.00000;,
 -0.80000;2.00000;0.00000;,
 -0.80000;0.00000;0.00000;,
 0.80000;0.00000;0.00000;,
 0.80000;-0.00000;0.40000;;
 
 18;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;12,10,7,6;,
 4;9,8,11,13;,
 4;14,15,16,3;,
 4;0,17,18,19;,
 4;19,18,15,14;,
 4;12,17,16,13;,
 4;10,12,13,11;,
 4;15,9,13,16;,
 4;17,12,6,18;,
 4;18,6,9,15;,
 4;4,19,14,5;,
 4;1,0,19,4;,
 4;5,14,3,2;,
 4;17,0,3,16;;
 
 MeshMaterialList {
  1;
  18;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   0.500000;
   0.000000;0.000000;0.000000;;
   0.500000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  9;
  0.000000;0.000000;-1.000000;,
  0.000000;0.484769;-0.874642;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.484769;0.874642;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.847998;-0.529999;,
  0.000000;0.847998;0.529999;;
  18;
  4;2,2,2,2;,
  4;4,4,5,5;,
  4;3,3,3,3;,
  4;0,0,1,1;,
  4;6,6,6,6;,
  4;7,1,1,7;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;8,8,8,8;,
  4;6,6,6,6;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;6,6,6,6;,
  4;5,8,8,5;,
  4;2,2,2,2;;
 }
 MeshTextureCoords {
  20;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
 MeshVertexColors {
  20;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;;
 }
}