#include "VertexShader.h"
#include "GraphicsThrowMacros.h"


VertexShader::VertexShader(Graphics& gfx, const std::wstring& path)
{
	INFOMAN(gfx);

	GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &pBytecodeBlob));
	auto bufferSize = pBytecodeBlob->GetBufferSize();
	GFX_THROW_INFO(GetDevice(gfx)->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),	//*pShaderBytecode,A pointer to the compiled shader
		pBytecodeBlob->GetBufferSize(),		//BytecodeLength,Size of the compiled vertex shader.
		nullptr,							//*pClassLinkage,A pointer to a class linkage interface (see ID3D11ClassLinkage); the value can be NULL.
		&pVertexShader						//Address of a pointer to a ID3D11VertexShader interface. If this is NULL, all other parameters will be validated, and if all parameters pass validation this API will return S_FALSE instead of S_OK.
	));
}

void VertexShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() const noexcept
{
	return pBytecodeBlob.Get();
}