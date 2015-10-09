#pragma once
#include "Vertex.h"
#include <vector>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Mesh
{
private:
	ID3D11Device** mDevice;

	Vertex* mVertices;
	int mNrOfVertices;
	ID3D11Buffer* mVertexBuffer;

	void LoadDefaultOBJMesh();
	void LoadOBJMeshFromFile(string fileName);
	void LoadMAYAOBJMeshFromFile(string fileName);
	void CreateVertexBuffer();
protected:

public:
	Mesh(ID3D11Device** device, string fileName);
	~Mesh();

	ID3D11Buffer** GetVertexBuffer() { return &mVertexBuffer; }
	int GetNrOfVertices() { return mNrOfVertices; }
};

Mesh::Mesh(ID3D11Device** device, string fileName)
{
	mDevice = device;

	LoadMAYAOBJMeshFromFile(fileName);
	CreateVertexBuffer();
}

Mesh::~Mesh()
{
	mVertexBuffer->Release();
	delete mVertices;
}

void Mesh::LoadOBJMeshFromFile(string fileName)
{
	vector<Vertex> vertexList;
	vector<XMFLOAT3> v;
	vector<XMFLOAT2> vt;
	vector<XMFLOAT3> vn;

	string line;
	ifstream myFile(fileName);
	if (myFile.is_open())
	{
		string nrLine = "";
		float fl3[3];
		float fl2[2];
		int flNr = 0;

		while (getline(myFile, line))
		{
			//READ VERTEX DATA
			if (line[0] == 'v')
			{
				if (line[1] == 't')
				{
					for (unsigned int i = 3; i < line.length() + 1; i++)
					{
						if (line[i] == ' ' || line[i] == '\0')
						{
							fl2[flNr++] = (float)atof(nrLine.c_str());
							nrLine = "";
						}
						else
						{
							nrLine += line[i];
						}
					}
					vt.push_back(XMFLOAT2(fl2[0], fl2[1]));
					flNr = 0;
				}
				else if (line[1] == 'n')
				{
					for (unsigned int i = 3; i < line.length() + 1; i++)
					{
						if (line[i] == ' ' || line[i] == '\0')
						{
							fl3[flNr++] = (float)atof(nrLine.c_str());
							nrLine = "";
						}
						else
						{
							nrLine += line[i];
						}
					}
					vn.push_back(XMFLOAT3(fl3[0], fl3[1], fl3[2]));
					flNr = 0;
				}
				else
				{
					for (unsigned int i = 2; i < line.length() + 1; i++)
					{
						if (line[i] == ' ' || line[i] == '\0')
						{
							fl3[flNr++] = (float)atof(nrLine.c_str());
							nrLine = "";
						}
						else
						{
							nrLine += line[i];
						}
					}
					v.push_back(XMFLOAT3(fl3[0], fl3[1], fl3[2]));
					flNr = 0;
				}
			}
			else if (line[0] == 'f')
			{
				//COMBINE
				for (unsigned int i = 2; i < line.length() + 1; i++)
				{
					if (line[i] == ' ' || line[i] == '\0')
					{
						string inLine = "";
						unsigned long vData[3];
						int nrVData = 0;
						for (unsigned int n = 0; n < nrLine.length() + 1; n++)
						{
							if (nrLine[n] == '/' || nrLine[n] == '\0')
							{
								vData[nrVData++] = (unsigned long)stol(inLine);
								inLine = "";
							}
							else
							{
								inLine += nrLine[n];
							}
						}
						Vertex vertex;
						vertex.pos = v.at(vData[0] - 1);
						vertex.pos.x *= 1;
						vertex.pos.y *= 1;
						vertex.pos.z *= 1;
						vertex.uv = vt.at(vData[1] - 1);
						vertex.normal = vn.at(vData[2] - 1);
						vertexList.push_back(vertex);

						nrLine = "";
					}
					else
					{
						nrLine += line[i];
					}
				}
			}
		}
		myFile.close();

		v.clear();
		v.shrink_to_fit();

		vt.clear();
		vt.shrink_to_fit();

		vn.clear();
		vn.shrink_to_fit();

		mNrOfVertices = vertexList.size();
		mVertices = new Vertex[mNrOfVertices];
		for (int i = 0; i < mNrOfVertices; i++)
		{
			mVertices[i] = vertexList.at(i);
		}

		vertexList.clear();
		vertexList.shrink_to_fit();
	}
	else
	{
		LoadDefaultOBJMesh();
	}
}

void Mesh::LoadMAYAOBJMeshFromFile(string fileName)
{
	struct Quad 
	{
		Vertex vertex[4];
	};
	vector<Quad> quadList;
	//vector<Vertex> vertexList;
	vector<XMFLOAT3> v;
	vector<XMFLOAT2> vt;
	vector<XMFLOAT3> vn;

	string line;
	ifstream myFile(fileName);
	if (myFile.is_open())
	{
		string nrLine = "";
		float fl3[3];
		float fl2[2];
		int flNr = 0;

		while (getline(myFile, line))
		{
			//READ VERTEX DATA
			if (line[0] == 'v')
			{
				if (line[1] == 't')
				{
					for (unsigned int i = 3; i < line.length() + 1; i++)
					{
						if (line[i] == ' ' || line[i] == '\0')
						{
							fl2[flNr++] = (float)atof(nrLine.c_str());
							nrLine = "";
						}
						else
						{
							nrLine += line[i];
						}
					}
					vt.push_back(XMFLOAT2(fl2[0], fl2[1]));
					flNr = 0;
				}
				else if (line[1] == 'n')
				{
					for (unsigned int i = 3; i < line.length() + 1; i++)
					{
						if (line[i] == ' ' || line[i] == '\0')
						{
							fl3[flNr++] = (float)atof(nrLine.c_str());
							nrLine = "";
						}
						else
						{
							nrLine += line[i];
						}
					}
					vn.push_back(XMFLOAT3(fl3[0], fl3[1], fl3[2]));
					flNr = 0;
				}
				else
				{
					for (unsigned int i = 2; i < line.length() + 1; i++)
					{
						if (line[i] == ' ' || line[i] == '\0')
						{
							fl3[flNr++] = (float)atof(nrLine.c_str());
							nrLine = "";
						}
						else
						{
							nrLine += line[i];
						}
					}
					v.push_back(XMFLOAT3(fl3[0], fl3[1], fl3[2]));
					flNr = 0;
				}
			}
			else if (line[0] == 'f')
			{
				//COMBINE
				int quadNr = 0;
				Quad quad;
				for (unsigned int i = 2; i < line.length() + 1; i++)
				{
					if (line[i] == ' ' || line[i] == '\0')
					{
						string inLine = "";
						unsigned long vData[3];
						int nrVData = 0;
						for (unsigned int n = 0; n < nrLine.length() + 1; n++)
						{
							if (nrLine[n] == '/' || nrLine[n] == '\0')
							{
								vData[nrVData++] = (unsigned long)stol(inLine);
								inLine = "";
							}
							else
							{
								inLine += nrLine[n];
							}
						}
						Vertex vertex;
						vertex.pos = v.at(vData[0] - 1);
						vertex.pos.x *= 1;
						vertex.pos.y *= 1;
						vertex.pos.z *= 1;
						vertex.uv = vt.at(vData[1] - 1);
						vertex.normal = vn.at(vData[2] - 1);
						//vertexList.push_back(vertex);

						quad.vertex[quadNr] = vertex;
						quadNr++; //Check 0-3
						nrLine = "";
					}
					else
					{
						nrLine += line[i];
					}
				}
				quadList.push_back(quad);
			}
		}
		myFile.close();

		v.clear();
		v.shrink_to_fit();

		vt.clear();
		vt.shrink_to_fit();

		vn.clear();
		vn.shrink_to_fit();

		mNrOfVertices = quadList.size()*2*3;
		mVertices = new Vertex[mNrOfVertices];
		int n = 0;
		for (unsigned int i = 0; i < quadList.size(); i++)
		{
			mVertices[n++] = quadList.at(i).vertex[0];
			mVertices[n++] = quadList.at(i).vertex[1];
			mVertices[n++] = quadList.at(i).vertex[2];

			mVertices[n++] = quadList.at(i).vertex[0];
			mVertices[n++] = quadList.at(i).vertex[2];
			mVertices[n++] = quadList.at(i).vertex[3];
			//for (int m = 1; m < 4; m++)
			//{
			//	//mVertices[n++] = quadList.at(i).vertex[m];
			//}
		}

		//vertexList.clear();
		//vertexList.shrink_to_fit();

		quadList.clear();
		quadList.shrink_to_fit();
	}
	else
	{
		LoadDefaultOBJMesh();
	}
}

void Mesh::LoadDefaultOBJMesh()
{
	mNrOfVertices = 3;
	mVertices = new Vertex[mNrOfVertices];

	mVertices[0].pos = XMFLOAT3(0.0f, 0.5f, 0.0f);
	mVertices[0].uv = XMFLOAT2(0.5f, 0.0f);
	mVertices[0].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	
	mVertices[1].pos = XMFLOAT3(0.5f, -0.5f, 0.0f);
	mVertices[1].uv = XMFLOAT2(1.0f, 1.0f);
	mVertices[1].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	mVertices[2].pos = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	mVertices[2].uv = XMFLOAT2(0.0f, 1.0f);
	mVertices[2].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
}

void Mesh::CreateVertexBuffer()
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	memset(&vertexBufferDesc, 0, sizeof(vertexBufferDesc));
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * mNrOfVertices;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	vertexBufferData.pSysMem = mVertices;

	(*mDevice)->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &mVertexBuffer);
}