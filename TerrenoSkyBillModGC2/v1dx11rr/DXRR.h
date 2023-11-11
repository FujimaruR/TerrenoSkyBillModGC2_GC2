#ifndef _dxrr
#define _dxrr
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "TerrenoRR.h"
#include "Camara.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "ModeloRR.h"
#include "XACT3Util.h"

#include "GUI.h"
#include "Text.h"

//hola, esto es una prueba

class DXRR{	

private:
	int ancho;
	int alto;
public:	
	HINSTANCE hInstance;
	HWND hWnd;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisabledState;

	ID3D11BlendState *alphaBlendState, *commonBlendState;

	int frameBillboard;

//INTERFAZ UI
	//reputacion
		GUI* alta;
		GUI* media;
		GUI* baja;
	//inputs
		GUI* teclas;
		GUI* pedidos;
		GUI* hawE;
		GUI* pepE;
	//inventario
		GUI* vacio;
		GUI* pep;
		GUI* haw;
		GUI* amb;
	//Final
		GUI* ganar;
		GUI* perder;
		GUI* malReputacion;
		GUI* malTiempo;


	GUI* diaUI;
	GUI* tardeUI;
	GUI* nocheUI;

	TerrenoRR *terreno;
	SkyDome *skydome;
	BillboardRR *billboard;
	BillboardRR* chica;//xd billboard
	BillboardRR* chico;

	BillboardRR* arbol1;
	BillboardRR* arbol2;
	BillboardRR* arbol3;

	Camara *camara;

	//modelos xd
	ModeloRR* edificio=0;
	ModeloRR* pizza;//pep
	ModeloRR* pizza2;//haw
	ModeloRR* pizzeria;
	ModeloRR* repartidor;
	ModeloRR* moto;
	ModeloRR* mesa;
	ModeloRR* casa1;
	ModeloRR* casa2;
	ModeloRR* casa3;

	float izqder;
	float arriaba;
	float vel;

	float velIzqDer;//xd
	float rotCam;//xd

	bool breakpoint;
	vector2 uv1[32];
	vector2 uv2[32];
	vector2 uv3[32];
	vector2 uv4[32];

	XACTINDEX cueIndex;
	CXACT3Util m_XACT3;
	D3DXVECTOR3 posCam;
	
	//jugabilidad 
	bool inventario;

	bool peperoni;
	bool hawaiana;
	bool ambos;

	bool pedidosQ;

	float tiempo;
	float reputacion;

	bool clientePep;
	bool clienteHaw;

	bool pedido1;
	bool pedido2;

	int seleccion;

	int pedidosCumplidos;

	bool Win;//senial de que ganaste el juego, servira para quitar la UI
	bool Lose;

	//COLOR DEL CIELO
	D3DXVECTOR4 colorSky;

	Text* texto;
    DXRR(HWND hWnd, int Ancho, int Alto)
	{
		breakpoint = false;
		frameBillboard = 0;
		ancho = Ancho;
		alto = Alto;
		driverType = D3D_DRIVER_TYPE_NULL;
		featureLevel = D3D_FEATURE_LEVEL_11_0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
		IniciaD3D(hWnd);
		izqder = 0;
		arriaba = 0;
		billCargaFuego();
		camara = new Camara(D3DXVECTOR3(0,80,6), D3DXVECTOR3(0,80,0), D3DXVECTOR3(0,1,0), Ancho, Alto);
		terreno = new TerrenoRR(300, 300, d3dDevice, d3dContext);
		skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"Sky/sky_2.jpg", L"Sky/skydome_Tarde.jpg", L"Sky/SkyNoche.png");
		billboard = new BillboardRR(L"Assets/Billboards/fuego-anim.png",L"Assets/Billboards/fuego-anim-normal.png", d3dDevice, d3dContext, 5);
		
		edificio = new ModeloRR(d3dDevice, d3dContext, "Assets/edificio/edificio.obj", L"Assets/edificio/edificio_1.jpg", L"Assets/noSpecMap.jpg", 0, 0);

		pizzeria = new ModeloRR(d3dDevice, d3dContext, "Assets/Pizzeria/Pizzeria.obj", L"Assets/Pizzeria/pizzeria.jpg", L"Assets/noSpecMap.jpg", 0, 0);
		pizza = new ModeloRR(d3dDevice, d3dContext, "Assets/Pizza/Pizza.obj", L"Assets/Pizza/pizza.jpg", L"Assets/noSpecMap.jpg", 0, 0);
		pizza2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Pizza2/Pizza.obj", L"Assets/Pizza2/pizza.jpg", L"Assets/noSpecMap.jpg", 0, 0);

		repartidor = new ModeloRR(d3dDevice, d3dContext, "Assets/Repartidor/Repartidor.obj", L"Assets/Repartidor/cuerpo_del_personaje.jpg", L"Assets/noSpecMap.jpg", 0, 0);
		moto= new ModeloRR(d3dDevice, d3dContext, "Assets/Moto/moto.obj", L"Assets/Moto/Scooter.jpg", L"Assets/noSpecMap.jpg", 0, 0);
		mesa = new ModeloRR(d3dDevice, d3dContext, "Assets/Mesa/Mesa.obj", L"Assets/Mesa/mesa.jpg", L"Assets/noSpecMap.jpg", 0, 0);
		casa1 = new ModeloRR(d3dDevice, d3dContext, "Assets/casa1/casa1.obj", L"Assets/casa1/houses.jpg", L"Assets/noSpecMap.jpg", 0, 0);
		casa2 = new ModeloRR(d3dDevice, d3dContext, "Assets/casa2/casa2.obj", L"Assets/casa1/houses.jpg", L"Assets/noSpecMap.jpg", 0, 0);
		casa3 = new ModeloRR(d3dDevice, d3dContext, "Assets/casa3/casa3.obj", L"Assets/casa1/houses.jpg", L"Assets/noSpecMap.jpg", 0, 0);
		
		//INTERFAZ
			vacio= new GUI(d3dDevice, d3dContext, 0.8, 1.0, L"Assets/UI/inventario/vacio.png");
			pep = new GUI(d3dDevice, d3dContext, 0.8, 1.0, L"Assets/UI/inventario/peperoni.png");
			haw = new GUI(d3dDevice, d3dContext, 0.8, 1.0, L"Assets/UI/inventario/hawaiana.png");
			amb = new GUI(d3dDevice, d3dContext, 0.8, 1.0, L"Assets/UI/inventario/ambas.png");
		//reputacion
			alta= new GUI(d3dDevice, d3dContext, 0.3, 0.5, L"Assets/UI/reputacion/alta.png");
			media = new GUI(d3dDevice, d3dContext, 0.3, 0.5, L"Assets/UI/reputacion/media.png");
			baja = new GUI(d3dDevice, d3dContext, 0.3, 0.5, L"Assets/UI/reputacion/baja.png");
		//input
			teclas= new GUI(d3dDevice, d3dContext, 0.8, 0.3, L"Assets/UI/teclas/teclas.png");
			pedidos = new GUI(d3dDevice, d3dContext, 0.8, 1.0, L"Assets/UI/teclas/pedidosxd.png");
			hawE = new GUI(d3dDevice, d3dContext, 0.5, 0.5, L"Assets/UI/teclas/haw2.png");
			pepE = new GUI(d3dDevice, d3dContext, 0.5, 0.5, L"Assets/UI/teclas/pep.png");
		
		//ciclo dia noche
			diaUI = new GUI(d3dDevice, d3dContext, 0.4, 0.4, L"Assets/UI/ciclo/diaxd.png");
			tardeUI = new GUI(d3dDevice, d3dContext, 0.4, 0.4, L"Assets/UI/ciclo/tardexd.png");
			nocheUI = new GUI(d3dDevice, d3dContext, 0.4, 0.4, L"Assets/UI/ciclo/nochexd.png");
		
		//final
			ganar= new GUI(d3dDevice, d3dContext, 2.0, 2.0, L"Assets/UI/fin/ganaste.png");
			perder= new GUI(d3dDevice, d3dContext, 2.0, 2.0, L"Assets/UI/fin/perdiste.png");
			malTiempo = new GUI(d3dDevice, d3dContext, 2.0, 2.0, L"Assets/UI/fin/malTiempo.png");
			malReputacion = new GUI(d3dDevice, d3dContext, 2.0, 2.0, L"Assets/UI/fin/malReputacion.png");

		velIzqDer = 0;//xd
		rotCam = 0;//xd
		
		//BILLBOARD
			chica = new BillboardRR(L"Assets/Billboards/nina.png", L"Assets/Billboards/nNormal.png", d3dDevice, d3dContext, 5);//xd
			chico = new BillboardRR(L"Assets/Billboards/pocoyo.png", L"Assets/Billboards/nNormal.png", d3dDevice, d3dContext, 5);

			arbol1 = new BillboardRR(L"Assets/Billboards/arbol1.png", L"Assets/Billboards/nNormal.png", d3dDevice, d3dContext, 5);
			arbol2 = new BillboardRR(L"Assets/Billboards/arbol2.png", L"Assets/Billboards/nNormal.png", d3dDevice, d3dContext, 5);
			arbol3 = new BillboardRR(L"Assets/Billboards/cerezo.png", L"Assets/Billboards/nNormal.png", d3dDevice, d3dContext, 5);

		inventario = false;
		pedidosQ = false;

		peperoni = false;
		hawaiana = false;
		ambos = false;

		tiempo = 60;
		texto = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/UI/fuente/font.png", XMFLOAT4(0.0f, 1.0f, 1.0f, 0.0f));
		reputacion = 100;
		
		clientePep = false;
		clienteHaw = false;

		pedido1 = false;
		pedido2 = false;

		seleccion = 0;//peperoni

		Win = false;
		Lose = false;

		//INICIAR COLOR CIELO
		colorSky[0] = 1.0;
		colorSky[1] = 1.0;
		colorSky[2] = 1.0;
		colorSky[3] = 1.0;

	}

	~DXRR()
	{
		//LiberaD3D();
		m_XACT3.Terminate();
	}
	
	bool IniciaD3D(HWND hWnd)
	{
		this->hInstance = hInstance;
		this->hWnd = hWnd;

		//obtiene el ancho y alto de la ventana donde se dibuja
		RECT dimensions;
		GetClientRect(hWnd, &dimensions);
		unsigned int width = dimensions.right - dimensions.left;
		unsigned int heigth = dimensions.bottom - dimensions.top;

		//Las formas en como la pc puede ejecutar el DX11, la mas rapida es D3D_DRIVER_TYPE_HARDWARE pero solo se puede usar cuando lo soporte el hardware
		//otra opcion es D3D_DRIVER_TYPE_WARP que emula el DX11 en los equipos que no lo soportan
		//la opcion menos recomendada es D3D_DRIVER_TYPE_SOFTWARE, es la mas lenta y solo es util cuando se libera una version de DX que no sea soportada por hardware
		D3D_DRIVER_TYPE driverTypes[]=
		{
			D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
		};
		unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

		//La version de DX que utilizara, en este caso el DX11
		D3D_FEATURE_LEVEL featureLevels[]=
		{
			D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
		};
		unsigned int totalFeaturesLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = heigth;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		HRESULT result;
		unsigned int driver = 0, creationFlags = 0;
		for(driver = 0; driver<totalDriverTypes; driver++)
		{
			result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0,
				creationFlags, featureLevels, totalFeaturesLevels, 
				D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
				&d3dDevice, &featureLevel, &d3dContext);

			if(SUCCEEDED(result))
			{
				driverType = driverTypes[driver];
				break;
			}
		}

		if(FAILED(result))
		{

			//Error al crear el Direct3D device
			return false;
		}
		
		ID3D11Texture2D* backBufferTexture;
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		if(FAILED(result))
		{
			//"Error al crear el swapChainBuffer
			return false;
		}

		result = d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget);
		if(backBufferTexture)
			backBufferTexture->Release();

		if(FAILED(result))
		{
			//Error al crear el renderTargetView
			return false;
		}


		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)heigth;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		d3dContext->RSSetViewports(1, &viewport);

		D3D11_TEXTURE2D_DESC depthTexDesc;
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = width;
		depthTexDesc.Height = heigth;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;
		
		result = d3dDevice->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthTexDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		result = d3dDevice->CreateDepthStencilView(depthTexture, &descDSV, &depthStencilView);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
			return false;
		}

		d3dContext->OMSetRenderTargets(1, &backBufferTarget, depthStencilView);

		//Audio xd
		bool res = m_XACT3.Initialize();
		if (!res)return res;

		res = m_XACT3.LoadWaveBank(L"Assets\\Audio\\WaveBank.xwb");
		if (!res) return res;
		res = m_XACT3.LoadSoundBank(L"Assets\\Audio\\Sound Bank.xsb");
		if (!res) return res;

		cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("fondoJuego");
		m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);

		return true;			
		
	}

	void LiberaD3D(void)
	{
		if(depthTexture)
			depthTexture->Release();
		if(depthStencilView)
			depthStencilView->Release();
		if(backBufferTarget)
			backBufferTarget->Release();
		if(swapChain)
			swapChain->Release();
		if(d3dContext)
			d3dContext->Release();
		if(d3dDevice)
			d3dDevice->Release();

		//reputacion
		delete alta;
		delete media;
		delete baja;
		//inputs
		delete teclas;
		delete pedidos;
		delete hawE;
		delete pepE;
		//inventario
		delete vacio;
		delete pep;
		delete haw;
		delete amb;
		//Final
		delete ganar;
		delete perder;
		delete malReputacion;
		delete malTiempo;

		delete diaUI;
		delete tardeUI;
		delete nocheUI;

		delete terreno;
		delete skydome;
		//delete billboard;
		//delete chica;//xd billboard
		//delete chico;
		//delete arbol1;
		//delete arbol2;
		//delete arbol3;

		//delete camara;

		//modelos xd
		delete pizza; //pep
		delete pizza2;//haw
		delete pizzeria;
		delete repartidor;
		delete moto;
		delete mesa;
		delete casa1;
		delete casa2;
		delete casa3;
		delete edificio;
		
		edificio = nullptr;
		alta = nullptr;
		media = nullptr;
		baja = nullptr;
		teclas = nullptr;
		pedidos = nullptr;
		hawE = nullptr;
		pepE = nullptr;
		vacio = nullptr;
		pep = nullptr;
		haw = nullptr;
		amb = nullptr;
		ganar = nullptr;
		perder = nullptr;
		malReputacion = nullptr;
		malTiempo = nullptr;
		diaUI = nullptr;
		tardeUI = nullptr;
		nocheUI = nullptr;

		terreno = nullptr;
		skydome = nullptr;
		//billboard = nullptr;
		//chica = nullptr;//xd billboard
		//chico = nullptr;
		//arbol1 = nullptr;
		//arbol2 = nullptr;
		//arbol3 = nullptr;
		//camara = nullptr;

		depthTexture = 0;
		depthStencilView = 0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;

	}
	
	void Render(void)
	{
		rotCam += izqder;//xd
		float sphere[3] = { 0,0,0 };
		float prevPos[3] = { camara->posCam.x, camara->posCam.z, camara->posCam.z };
		static float angle = 0.0f;
		angle += 0.005;
		if (angle >= 360) angle = 0.0f;
		bool collide = false;
		if (d3dContext == 0)
			return;
		
		colorSky.x = skydome->colores[0] / 2;
		colorSky.y = skydome->colores[1] / 2;
		colorSky.z = skydome->colores[2] / 2;
		colorSky.w = skydome->colores[3] / 2;
		float clearColor[4] = { 0, 0, 0, 1.0f };
		d3dContext->ClearRenderTargetView(backBufferTarget, clearColor);
		d3dContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		camara->posCam.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 5;

		skydome->Update(camara->vista, camara->proyeccion);

		float camPosXZ[2] = { camara->posCam.x, camara->posCam.z };

		TurnOffDepth();
		skydome->Render(camara->posCam);
		TurnOnDepth();
		terreno->Draw(camara->vista, camara->proyeccion);

		//BILLBOARD
		//animado
		//billboard->Draw(camara->vista, camara->proyeccion, camara->posCam,
		//	-11, -78, 4, 5, true, uv1, uv2, uv3, uv4, frameBillboard);

		//sin animar
		chica->Draw(camara->vista, camara->proyeccion, camara->posCam,
			0, 80, terreno->Superficie(0, 80), 3, false);

		chico->Draw(camara->vista, camara->proyeccion, camara->posCam,
			40, 40, terreno->Superficie(40, 40), 3, false);
		//frente al edificio
		arbol2->Draw(camara->vista, camara->proyeccion, camara->posCam,
			10, 30, terreno->Superficie(10, 30), 10, false);
		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-50, 30, terreno->Superficie(0, 30), 10, false);
		arbol2->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-95, 70, terreno->Superficie(-40, 10), 10, false);

		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			10, -80, terreno->Superficie(-5, -50),10, false);
		arbol2->Draw(camara->vista, camara->proyeccion, camara->posCam,
			15, -70, terreno->Superficie(40, 100), 10, false);

		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			10, -80, terreno->Superficie(-5, -50), 10, false);
		arbol2->Draw(camara->vista, camara->proyeccion, camara->posCam,
			15, -70, terreno->Superficie(40, 100), 10, false);

		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			40, 80, terreno->Superficie(50, 80), 10, false);

		arbol2->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-50, 80, terreno->Superficie(-50, 80), 10, false);

		//arboles sustitutos
		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			40, -60, terreno->Superficie(40, -60), 10, false);
		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			40, -40, terreno->Superficie(40, -40), 10, false);
		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			40, -20, terreno->Superficie(40, -20), 10, false);
		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			40, 0, terreno->Superficie(40, 0), 10, false);

		//lado del lago
		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-120, -60, terreno->Superficie(40, -60), 10, false);
		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-120, 0, terreno->Superficie(40, 0), 10, false);

		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-40, -80, terreno->Superficie(40, 0), 10, false);

		//MODELOS
		edificio->setPosX(5.0f);
		edificio->setPosZ(100.0f);
		edificio->Draw(camara->vista, camara->proyeccion, terreno->Superficie(edificio->getPosX(), edificio->getPosZ()), camara->posCam, 10.0f, 0, 'A', 0.5);
		
		pizzeria->setPosX(-20.0f);
		pizzeria->setPosZ(-80.0f);
		pizzeria->Draw(camara->vista, camara->proyeccion, terreno->Superficie(pizzeria->getPosX(), pizzeria->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1);
		
		mesa->setPosX(-15.0f);
		mesa->setPosZ(-75.0f);
		mesa->Draw(camara->vista, camara->proyeccion, terreno->Superficie(mesa->getPosX(), mesa->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1);

		repartidor->setPosX(-20.0f);
		repartidor->setPosZ(-80.0f);
		repartidor->Draw(camara->vista, camara->proyeccion, terreno->Superficie(repartidor->getPosX(), repartidor->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1);
		
		if (peperoni == false) {
			pizza->setPosX(-16.0f);
			pizza->setPosZ(-75.0f);
			pizza->Draw(camara->vista, camara->proyeccion, terreno->Superficie(pizza->getPosX(), pizza->getPosZ()) + 4, camara->posCam, 10.0f, 0, 'A', 1);

		}
		if (hawaiana == false) {
			pizza2->setPosX(-13.0f);
			pizza2->setPosZ(-75.0f);
			pizza2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(pizza->getPosX(), pizza->getPosZ()) + 4, camara->posCam, 10.0f, 0, 'A', 1);

		}
		//Camara en el modelo 
		//le pasamos la posicion de la camara en x y z
		moto->setPosX(camara->posCam.x);
		moto->setPosZ(camara->posCam.z);
		moto->Draw(camara->vista, camara->proyeccion, terreno->Superficie(moto->getPosX(), moto->getPosZ()), camara->posCam, 10.0f,  rotCam, 'Y', 1);
		// rotCam almacena el valor de rotacion de la camara, para que el modelo rote junto con el movimiento de la camara
		// la letra "Y" representa la rotacion en Y, si pones cualquier otra letra no hara nada, tiene que ser X, Y o Z para que haga algo

		casa1->setPosX(-80.0f);
		casa1->setPosZ(80.0f);
		casa1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(casa1->getPosX(), casa1->getPosZ()), camara->posCam, 10.0f, 180 * (XM_PI / 180), 'Y', 1);

		casa2->setPosX(50.0f);
		casa2->setPosZ(30.0f);
		casa2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(casa2->getPosX(), casa2->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1);

		casa3->setPosX(-30.0f);
		casa3->setPosZ(100.0f);
		casa3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(casa3->getPosX(), casa3->getPosZ()), camara->posCam, 10.0f, 180*(XM_PI/180), 'Y', 1);
		
		//INTERFAZ UI

		if (Win == false && Lose ==false) {
			teclas->Draw(0.8f, 0.2f);
			if (inventario == true) {

				if (peperoni && hawaiana) {
					amb->Draw(0.0f, -0.8f);
				}else if(peperoni)
					pep->Draw(0.0f, -0.8f);
				else if(hawaiana)
					haw->Draw(0.0f, -0.8f);
				else
					vacio->Draw(0.0f, -0.8f);

			}
			if (pedidosQ == true) {
				pedidos->Draw(0.0f, 0.0f);
			}
			//TEXTO
			if (tiempo >= 0)
				tiempo -= 0.01;
			TurnOnAlphaBlending();
			//texto->DrawText(0.5f, 0.7f, "Tiempo: " + texto->Time(tiempo), 0.015);
			texto->DrawText(0.8f, 0.68f, texto->Time(tiempo), 0.015);
			//texto->DrawText(0.5f, 0.68f, texto->Time(reputacion), 0.015);
			if (tiempo < 60 && tiempo>55) {
				texto->DrawText(-0.5f, 0.0f, "Completa los pedidos pendientes...", 0.015);
			}
			if (seleccion == 0)
				texto->DrawText(-0.5f, -0.8f, "Vacio", 0.015);
			TurnOffAlphaBlending();

			if (seleccion == 1)
				pepE->Draw(-0.5f, -0.8f);
			if (seleccion == 2)
				hawE->Draw(-0.5f, -0.8f);

			//reputacion
			if (reputacion >= 0)
				reputacion -= 0.02;

			if (reputacion > 80)
				alta->Draw(-0.7f, 0.8f);
			if (reputacion <= 80 && reputacion > 30)
				media->Draw(-0.7f, 0.8f);
			if (reputacion <= 30)
				baja->Draw(-0.7f, 0.8f);
		}
			if(pedido1==true && pedido2==true){
				Win = true;
				ganar->Draw(0.0f, 0.0f);
			}
			if (tiempo <= 0) {
				Lose = true;
				malTiempo->Draw(0.0f, 0.0f);

			}
			if (reputacion <= 0) {
				Lose = true;
				malReputacion->Draw(0.0f, 0.0f);
			}

		//COLISION
		if (!isPointInsideSphere(camara->GetPoint(), casa1->GetSphere(10))&& 
			!isPointInsideSphere(camara->GetPoint(), mesa->GetSphere(3)) &&
			!isPointInsideSphere(camara->GetPoint(), casa2->GetSphere(13))&&
			!isPointInsideSphere(camara->GetPoint(), casa3->GetSphere(13))&&
			!isPointInsideSphere(camara->GetPoint(), edificio->GetSphere(15))){

			camara->UpdateCam(vel, velIzqDer, arriaba, izqder);//no se encuentra dentro de la esfera, entonces actualiza la posicion de la camara
		}
		else {
			camara->posCam = camara->posCamPast;//sino establece la camara en su posicion anterior para que no pase el limite de la esfera
		}
		//logica entregar pizzas a la casa correcta
		if (isPointInsideSphere(camara->GetPoint(), pizza->GetSphere(3))) { peperoni = true; }
		if (isPointInsideSphere(camara->GetPoint(), edificio->GetSphere(18))) { 
			clientePep = true; }
		else { clientePep = false; }

		if (clientePep == true && seleccion == 1 && peperoni ==true)//revisa...colision con cliente, tipo de pizza seleccionada y tener la pizza a la mano
		{
			reputacion = reputacion + 40;
			seleccion = 0;
			peperoni = false;
			pedido1 = true;
		}
		else if(clientePep == true && seleccion == 2 && hawaiana==true) {
			hawaiana = false;
			reputacion = reputacion - 40;
		}
		//logica pizza hawaiana
		if (isPointInsideSphere(camara->GetPoint(), pizza2->GetSphere(3))) { hawaiana = true; }
		if (isPointInsideSphere(camara->GetPoint(), casa2->GetSphere(18))) {
			clienteHaw = true;
		}
		else { clienteHaw = false; }
		if (clienteHaw == true && seleccion == 2 && hawaiana == true)
		{
			reputacion = reputacion + 40;
			seleccion = 0;
			hawaiana = false;
			pedido2 = true;
		}
		else if (clienteHaw == true && seleccion == 1 && peperoni == true) {
			peperoni = false;
			reputacion = reputacion - 40;
		}


		if (skydome->getSkydomeStatus() == 3 || skydome->getSkydomeStatus() == 0) {
			diaUI->Draw(0.8, 0.8);
		}
		else  if (skydome->getSkydomeStatus() == 1) {
			tardeUI->Draw(0.8, 0.8);
		}
		else if (skydome->getSkydomeStatus() == 2) {
			nocheUI->Draw(0.8, 0.8);
		}
		
		swapChain->Present( 1, 0 );
	}

	bool isPointInsideSphere(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));// se calcula la distancia entre la camara y la esfera(distancia entre dos puntos)

		if (distance < sphere[2])//si la distancia es menor al radio de la esfera entonces esta colisionando
			collition = true;
		return collition;
	}

	//Activa el alpha blend para dibujar con transparencias
	void TurnOnAlphaBlending()
	{

		float blendFactor[4];
		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;
		HRESULT result;

		D3D11_BLEND_DESC descABSD;
		ZeroMemory(&descABSD, sizeof(D3D11_BLEND_DESC));
		descABSD.RenderTarget[0].BlendEnable = TRUE;
		descABSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descABSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descABSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		result = d3dDevice->CreateBlendState(&descABSD, &alphaBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
	}

	//Regresa al blend normal(solido)
	void TurnOffAlphaBlending()
	{
		D3D11_BLEND_DESC descCBSD;
		ZeroMemory(&descCBSD, sizeof(D3D11_BLEND_DESC));
		descCBSD.RenderTarget[0].BlendEnable = FALSE;
		descCBSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descCBSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descCBSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		HRESULT result;

		result = d3dDevice->CreateBlendState(&descCBSD, &commonBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(commonBlendState, NULL, 0xffffffff);
	}

	void TurnOnDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDSD;
		ZeroMemory(&descDSD, sizeof(descDSD));
		descDSD.DepthEnable = true;
		descDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDSD.StencilEnable=true;
		descDSD.StencilReadMask = 0xFF;
		descDSD.StencilWriteMask = 0xFF;
		descDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDSD, &depthStencilState);
		
		d3dContext->OMSetDepthStencilState(depthStencilState, 1);
	}

	void TurnOffDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDDSD;
		ZeroMemory(&descDDSD, sizeof(descDDSD));
		descDDSD.DepthEnable = false;
		descDDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDDSD.StencilEnable=true;
		descDDSD.StencilReadMask = 0xFF;
		descDDSD.StencilWriteMask = 0xFF;
		descDDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDDSD, &depthStencilDisabledState);
		d3dContext->OMSetDepthStencilState(depthStencilDisabledState, 1);
	}

	void billCargaFuego()
	{
		uv1[0].u = .125;
		uv2[0].u = .125;
		uv3[0].u = 0;
		uv4[0].u = 0;

		uv1[0].v = .25;
		uv2[0].v = 0;
		uv3[0].v = 0;
		uv4[0].v = .25;


		for (int j = 0; j < 8; j++) {
			uv1[j].u = uv1[0].u + (j * .125);
			uv2[j].u = uv2[0].u + (j * .125);
			uv3[j].u = uv3[0].u + (j * .125);
			uv4[j].u = uv4[0].u + (j * .125);

			uv1[j].v = .25;
			uv2[j].v = 0;
			uv3[j].v = 0;
			uv4[j].v = .25;
		}
		for (int j = 0; j < 8; j++) {
			uv1[j + 8].u = uv1[0].u + (j * .125);
			uv2[j + 8].u = uv2[0].u + (j * .125);
			uv3[j + 8].u = uv3[0].u + (j * .125);
			uv4[j + 8].u = uv4[0].u + (j * .125);

			uv1[j + 8].v = .5;
			uv2[j + 8].v = .25;
			uv3[j + 8].v = .25;
			uv4[j + 8].v = .5;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 16].u = uv1[0].u + (j * .125);
			uv2[j + 16].u = uv2[0].u + (j * .125);
			uv3[j + 16].u = uv3[0].u + (j * .125);
			uv4[j + 16].u = uv4[0].u + (j * .125);

			uv1[j + 16].v = .75;
			uv2[j + 16].v = .5;
			uv3[j + 16].v = .5;
			uv4[j + 16].v = .75;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 24].u = uv1[0].u + (j * .125);
			uv2[j + 24].u = uv2[0].u + (j * .125);
			uv3[j + 24].u = uv3[0].u + (j * .125);
			uv4[j + 24].u = uv4[0].u + (j * .125);

			uv1[j + 24].v = 1;
			uv2[j + 24].v = .75;
			uv3[j + 24].v = .75;
			uv4[j + 24].v = 1;
		}
	}

};
#endif